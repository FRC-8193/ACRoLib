FROM wpilib/roborio-cross-ubuntu:2025-22.04

RUN apt-get update -y && apt-get install -y build-essential cmake

WORKDIR /workspace

COPY ./FRCMake/ /workspace/FRCMake
COPY ./CMakeLists.txt /workspace/CMakeLists.txt

RUN cmake -B build . && cmake --build build -j 16

WORKDIR /workspace

COPY ./cpp/ /workspace/cpp
COPY ./build_acrolib.cmake /workspace/build_acrolib.cmake

RUN cmake -B build . && cmake --build build
