FROM ubuntu:20.04

ENV SHELL /bin/bash

RUN apt-get update && apt-get install -y \
    vim \
    git \
    screen

RUN apt-get update && apt-get install -y \
    g++ \
    freeglut3-dev