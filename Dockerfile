FROM ubuntu:24.04

# Update package lists and install required packages
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    check \
    && rm -rf /var/lib/apt/lists/*

# Create a non-root user 'ubuntu'
RUN useradd -ms /bin/bash ubuntu

# Set the working directory
WORKDIR /datetime

# Copy the current directory contents into /datetime
COPY . /datetime

# Change ownership of /datetime to the user 'ubuntu'
RUN chown -R ubuntu:ubuntu /datetime

# End the container with an infinite sleep to keep it running
CMD ["sleep", "infinity"]
