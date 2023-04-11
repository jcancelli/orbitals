FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-22.04

ARG NODE_VERSION 18
ARG EMSDK_VERSION latest

SHELL ["/bin/bash", "-c"]

WORKDIR /emscripten

RUN apt-get update -y \
	&& apt-get upgrade -y \
	# install node
	&& curl -sL https://deb.nodesource.com/setup_${NODE_VERSION}.x -o node_setup.sh \
	&& source node_setup.sh \
	&& apt-get install -y nodejs \
	# install emscripten dependencies
	&& apt-get install -y git python3 cmake make \
	# install emscripten
	&& git clone https://github.com/emscripten-core/emsdk.git

WORKDIR /emscripten/emsdk

RUN git pull \
	&& ./emsdk install ${EMSDK_VERSION} \
	&& ./emsdk activate ${EMSDK_VERSION}

# edit emscripten config so that it uses the nodejs version already installed on the system
RUN sed -i "s/^NODE_JS.*\$/NODE_JS = 'node'/" .emscripten

USER vscode

# adds emscripten to PATH
RUN echo "export EMSDK_QUIET=1 && source /emscripten/emsdk/emsdk_env.sh && export EMSDK_QUIET=0" >> /home/vscode/.bashrc