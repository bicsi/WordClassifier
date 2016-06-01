CFLAGS=-std=c++11 -Wall -O2 -c

all: bloom_train

bloom_train: train.o bloom.o prime.o
	g++ train.o bloom.o prime.o -o bloom_train

train.o: src/main.cpp
	g++ $(CFLAGS) src/bloom_train.cpp -o train.o

bloom.o: src/bloom_classifier.cpp include/bloom_classifier.h
	g++ $(CFLAGS) src/bloom_classifier.cpp -o bloom.o

prime.o: src/random_gen.cpp include/random_gen.h
	g++ $(CFLAGS) src/random_gen.cpp -o prime.o

clean:
	rm *o bloom_train
