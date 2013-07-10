# Makefile for readPET

# LDFLAGS=
LDFLAGS=
# LDFLAGS=-R /usr/local/lib
# LDFLAGS=-R /opt/csw/lib
# CC=CC -g -I.
CC=g++ -g -I.

EHDR=Data.h
EOBJ=Data.o Model.o ModelLogan.o ModelPatlak.o Integrate.o
PETHEADERS=PET.h Advance.h Scanditronix.h
HEADERS=GEtypes.h idbConstants.h  dbh.h Header.h
OBJS=readPET.o Advance.o dbh.o PET.o Scanditronix.o GE6.o Timer.o Header.o

.SUFFIXES: .C .o

readPET: ${OBJS} ${EOBJ}
	${CC} ${LDFLAGS} -o readPET ${OBJS} ${EOBJ} -lm

readPET_mingw: ${OBJS} ${EOBJ}
	${CC} -o readPET_mingw ${OBJS} ${EOBJ} -lm

readPET_cygwin: ${OBJS} ${EOBJ}
	${CC} -o readPET_cygwin ${OBJS} ${EOBJ} -lm

.C.o: $?.h $?.C
	${CC} -c $<

readPET.o: readPET.C ${PETHEADERS} ${HEADERS} ${EHDR}
	${CC} -c readPET.C

Advance.o: Advance.C Advance.h Model.h ${HEADERS} ${EHDR} ${PETHEADERS}
	${CC} -c Advance.C

Scanditronix.o: Scanditronix.C Scanditronix.h PET.h GE6.h Model.h Data.h
	${CC} -c Scanditronix.C

Header.o: Header.C Header.h
	${CC} -c Header.C

GE6.o: GE6.C GE6.h
	${CC} -c GE6.C

PET.o: PET.C ${HEADERS} ${EHDR}
	${CC} -c PET.C

dbh.o: dbh.C ${HEADERS} ${EHDR}
	${CC} -c dbh.C

Data.o: Data.h Data.C ${HEADERS} ${EHDR}
	${CC} -c Data.C

ModelLogan.o: ModelLogan.h ModelLogan.C Model.h Data.h
	${CC} -c ModelLogan.C

ModelPatlak.o: ModelPatlak.h ModelPatlak.C Model.h Data.h
	${CC} -c ModelPatlak.C

Integrate.o: Integrate.C Data.h
	${CC} -c Integrate.C

Timer.o: Timer.C Timer.h
	${CC} -c Timer.C

clean:
	rm readPET *.o
