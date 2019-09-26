#-------------------------------------------------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See https://go.microsoft.com/fwlink/?linkid=2090316 for license information.
#-------------------------------------------------------------------------------------------------------------
FROM ros:dashing

# Avoid warnings by switching to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# Username for non-root user in docker container.
ARG USERNAME=uas

# Set this to your local system's uid (found using `id -u`)
ARG USER_UID=1000

# Set this to your local system's gid (found using `id -g`)
ARG USER_GID=$USER_UID

# Configure apt and install packages
RUN apt-get update \
    && apt-get -y install --no-install-recommends apt-utils dialog 2>&1 \
    #
    # Verify git, process tools, lsb-release (common in install instructions for CLIs) installed
    && apt-get -y install git procps lsb-release \
    #
    # Create a non-root user to use if preferred - see https://aka.ms/vscode-remote/containers/non-root-user.
    && groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    # [Optional] Uncomment the next three lines to add sudo support
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    #
    # Clean up
    && apt-get autoremove -y

# Install required packages
RUN apt-get -y install \
ninja-build ccache vim clang-format curl
RUN curl -sL https://deb.nodesource.com/setup_10.x | bash - && \
apt-get -y install nodejs

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=

###
# IF YOU WANT TO USE ROOT WITHIN DEV CONTAINER: uncomment the following
###

# RUN echo "source /opt/ros/dashing/local_setup.bash" >> /root/.bashrc

###
# ELSE, IF YOU WANT TO USE ROOT WITHIN DEV CONTAINER: uncomment the following
###

USER $USERNAME
RUN echo "source /opt/ros/dashing/local_setup.bash" >> /home/$USERNAME/.bashrc

###
# END OF ROOT/USER CONFIG
###
