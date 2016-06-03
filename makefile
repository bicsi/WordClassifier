CFLAGS=-std=c++11 -Wall -O2 -c

all: bloom_train rnn_test

rnn_test: rnn.o rnn_test.o tester.o
	g++ rnn.o rnn_test.o tester.o -o rnn_test -larmadillo

bloom_train: train.o bloom.o prime.o tester.o
	g++ train.o bloom.o prime.o tester.o -o bloom_train

rnn.o: src/rnn_classifier.cpp include/rnn_classifier.h
	g++ $(CFLAGS) -larmadillo src/rnn_classifier.cpp -o rnn.o

rnn_test.o: src/rnn_test.cpp
	g++ $(CFLAGS) src/rnn_test.cpp -o rnn_test.o

tester.o: src/model_tester.cpp include/model_tester.h
	g++ $(CFLAGS) src/model_tester.cpp -o tester.o

train.o: src/bloom_train.cpp
	g++ $(CFLAGS) src/bloom_train.cpp -o train.o

bloom.o: src/bloom_classifier.cpp include/bloom_classifier.h
	g++ $(CFLAGS) src/bloom_classifier.cpp -o bloom.o

prime.o: src/random_gen.cpp include/random_gen.h
	g++ $(CFLAGS) src/random_gen.cpp -o prime.o

clean:
	rm *o bloom_train rnn_test
