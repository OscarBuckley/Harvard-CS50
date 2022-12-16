SELECT movies.title FROM movies INNER JOIN stars ON stars.movie_id = movies.id INNER JOIN people ON stars.person_id = people.id WHERE stars.person_id = (SELECT id FROM people WHERE name = "Johnny Depp") INTERSECT SELECT movies.title FROM movies INNER JOIN stars ON stars.movie_id = movies.id INNER JOIN people ON stars.person_id = people.id WHERE stars.person_id = (SELECT id FROM people WHERE name = "Helena Bonham Carter");