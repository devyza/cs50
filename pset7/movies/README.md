# Movies (SQLite)

SQL queries to answer questions about movies from IMDb database.

**Specification**

1. List the title of all movies released in 2008.
2. The birth year of Emma Stone
3. The titles of all movies with a release date on or after 2018, in alphabetical order
4. The number of movies with an IMDb rating of 10.0.
5. The titles and release years of all Harry Potter movies, in chronological order.
6. The average rating of all movies released in 2012.
7. All movies released in 2010 and their ratings, in decending order by rating.
8. The names of all people who starred in Toy Story.
9. The names of all people who starred in a movie released in 2004, ordered by birth year.
10. All people who have directed a movie that received a rating of at least 9.0.
11. The titles of the five highest rated movies (in order) that Chadwick Boseman starred in starting with the highest rated.
12. The titles of all movies in which both Johnny Depp and Helena Boham Carter starstarred.
13. The names of all people who starred in a movie in which Kevin Bacon also starred.

See more information and download database database from [here](https://cs50.harvard.edu/x/2020/psets/7/movies/).

---
## Usage
    $ cat filename.sql | sqlite3 movies.db

## Example

The names of all people who starred in Toy Story.

    $ cat 8.sql | sqlite3 movies.db
    Tom Hanks
    Tim Allen
    Don Rickles
    Jim Varney