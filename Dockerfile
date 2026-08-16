## Stage 1: build

FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
	g++ \
	cmake \
	libboost-dev \
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF
RUN cmake --build build --config Release

## Stage 2: Runtime

FROM ubuntu:22.04

WORKDIR /app

COPY --from=builder /app/build/MiniRedis /usr/local/bin/MiniRedis

EXPOSE 6379

CMD ["MiniRedis"]
