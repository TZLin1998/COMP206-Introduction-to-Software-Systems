all:movie_recommender
movie_recommender:src/preferences.c preferences.o distances.o include/preferences.h include/distances.h
	gcc -o movie_recommender src/movie_recommender.c preferences.o distances.o -Iinclude
preferences.o: include/preferences.h src/preferences.c
	gcc -c src/preferences.c -Iinclude
distances.o: include/distances.h src/distances.c
	gcc -c src/distances.c -Iinclude

clean: 
	rm -rf *.o movie_recommender
