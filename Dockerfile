FROM ubuntu:24.04

# Update package lists and install required packages
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    libcheck-dev && \
    rm -rf /var/lib/apt/lists/*

# End the container with an infinite sleep to keep it running
CMD ["sleep", "infinity"]
