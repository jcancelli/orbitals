FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-22.04

ARG NODE_VERSION 18
ARG EMSDK_VERSION latest
ARG BOOST_VERSION_MAJOR
ARG BOOST_VERSION_MINOR
ARG BOOST_VERSION_PATCH

SHELL ["/bin/bash", "-c"]

ENV BOOST_VERSION ${BOOST_VERSION_MAJOR}.${BOOST_VERSION_MINOR}.${BOOST_VERSION_PATCH}
ENV BOOST_VERSION_UNDERSCORE ${BOOST_VERSION_MAJOR}_${BOOST_VERSION_MINOR}_${BOOST_VERSION_PATCH}

WORKDIR /emscripten

RUN apt-get update -y \
	&& apt-get upgrade -y \
	# install node
	&& curl -sL https://deb.nodesource.com/setup_${NODE_VERSION}.x -o node_setup.sh \
	&& source node_setup.sh \
	&& apt-get install -y nodejs \
	# install emscripten dependencies
	&& apt-get install -y git python3 cmake make \
	# clone emscripten repo
	&& git clone https://github.com/emscripten-core/emsdk.git

WORKDIR /emscripten/emsdk

RUN git pull \
	&& ./emsdk install ${EMSDK_VERSION} \
	&& ./emsdk activate ${EMSDK_VERSION}

# edit emscripten config so that it uses the nodejs version already installed on the system
RUN sed -i "s/^NODE_JS.*\$/NODE_JS = 'node'/" .emscripten

# install boost library
WORKDIR /
RUN wget https://boostorg.jfrog.io/artifactory/main/release/${BOOST_VERSION}/source/boost_${BOOST_VERSION_UNDERSCORE}.tar.gz
RUN tar -xvf boost_${BOOST_VERSION_UNDERSCORE}.tar.gz \
	&& rm boost_${BOOST_VERSION_UNDERSCORE}.tar.gz

# adds emscripten to PATH
USER vscode
WORKDIR /home/vscode
RUN echo "export EMSDK_QUIET=1 && source /emscripten/emsdk/emsdk_env.sh && export EMSDK_QUIET=0" >> .bashrc
ENV BOOST_ROOT /boost_${BOOST_VERSION_UNDERSCORE}

ENV CXX=/emscripten/emsdk/upstream/emscripten/em++