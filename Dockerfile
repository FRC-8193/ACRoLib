FROM wpilib/roborio-cross-ubuntu:2025-22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
	build-essential \
	cmake \
	git \
	curl

RUN git clone --filter=blob:none --no-checkout https://github.com/wpilibsuite/allwpilib.git /wpilib && \
    cd /wpilib && \
    git sparse-checkout init --cone && \
    git sparse-checkout set wpilibc cmake wpimath wpinet wpiunits wpiutil hal ntcore cameraserver && \
    git checkout HEAD

WORKDIR /workspace

COPY build-wpilib /workspace/build-wpilib

RUN cmake -B build build-wpilib -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build -j 8

COPY include/ /workspace
COPY src/ /workspace
COPY CMakeLists.txt /workspace

RUN cmake --build build
