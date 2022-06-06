FROM ubuntu:18.04
MAINTAINER SonodaKazuto

#VOLUME ["/home/project"]
WORKDIR /home/project

# Install packages
RUN apt update && apt upgrade -y
RUN apt install sudo zsh git nano curl -y
RUN sudo apt install build-essential m4 scons zlib1g zlib1g-dev libprotobuf-dev protobuf-compiler libprotoc-dev \
    libgoogle-perftools-dev python3-dev python3-six python libboost-all-dev pkg-config -y
COPY /scripts/install-ohmyzsh.sh /home/project/

# Load and build gem5
RUN mkdir -p home/project/gem5
ADD https://gem5.googlesource.com/public/gem5/+archive/525ce650e1a5bbe71c39d4b15598d6c003cc9f9e.tar.gz /home/project/gem5
#RUN tar -xvf gem5.tar.gz
#RUN rm -rf gem5.tar.gz
#RUN scons build/X86/gem5.opt -j8

# Load and build NVmain
RUN cd ..
RUN git clone https://github.com/SEAL-UCSB/NVmain
#RUN cd NVmain
#COPY /nvmain-solo-build/SConscript /home/project/NVmain
#RUN cd /NVmain
#RUN scons --build-type=fast -j8

# Hybrid build
#COPY /hybrid-build/SConscript /home/project/NVmain
#WORKDIR /home/project/gem5
#COPY /hybrid-build/Options.py /home/project/gem5/configs/common
#RUN scons EXTRAS=../NVmain build/X86/gem5.opt -j8
#RUN ./build/X86/gem5.opt configs/example/se.py -c tests/test-progs/hello/bin/x86/linux/hello --cpu-type=TimingSimpleCPU\
#     --caches --l2cache --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/PCM_ISSCC_2012_4GB.config \
#RUN cat /home/project/gem5/m5out/stats.txt

CMD [ 'apt update && apt upgarde -y' ]
