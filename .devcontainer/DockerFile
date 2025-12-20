# Use Ubuntu 22.04 
FROM ubuntu:22.04

ARG USER=dev
ARG UID=1000
ENV DEBIAN_FRONTEND=noninteractive

# Prepere the system and install the tools to run the program  (add cmake to compile gtest)
RUN apt-get update \
  && apt-get install -y --no-install-recommends \
  build-essential \
  cmake \
  git \
  gdb \
  gdbserver \
  ninja-build \
  clang \
  lldb \
  valgrind \
  make \
  sudo \
  ca-certificates \
  openssh-client \
  procps \
  libcurl4-openssl-dev \
  nlohmann-json3-dev \
  libgtest-dev \
  libcurl4-openssl-dev \
  nlohmann-json3-dev \
  && rm -rf /var/lib/apt/lists/*

# Compile and install  GoogleTest
RUN if [ -d /usr/src/googletest ] ; then \
  cd /usr/src/googletest && cmake . && make && cp -a lib/*.a /usr/lib/ || true ; \
  elif [ -d /usr/src/gtest ] ; then \
  cd /usr/src/gtest && cmake . && make && cp -a lib/*.a /usr/lib/ || true ; \
  fi

# Create non-root user with UID (used by devcontainer.json)    
RUN useradd -m -u ${UID} ${USER} \
  && echo "${USER} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USER} \
  && chmod 0440 /etc/sudoers.d/${USER}

# Working directory as expected by devcontainer.json 
WORKDIR /workspace

# Switch to non-root user
USER ${USER}

EXPOSE 2345

# Keep the container running (VS Code will use it)
ENTRYPOINT ["tail", "-f", "/dev/null"]
# curl handling

