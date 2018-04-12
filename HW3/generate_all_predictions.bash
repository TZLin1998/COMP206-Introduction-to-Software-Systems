#!/bin/bash
mv query/daves_preferences.txt data/
for fn in $(ls data)
        do
	mv data/$fn query/
        ./movie_recommender query/$fn data/*
	mv query/$fn data/
	done
mv data/daves_preferences.txt query/
