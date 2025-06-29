SELECT title, duration 
FROM track 
ORDER BY duration DESC 
LIMIT 1;

SELECT title 
FROM track 
WHERE duration >= '3:30';

SELECT title
FROM collection 
WHERE year BETWEEN 2018 AND 2020;

SELECT name 
FROM artist 
WHERE name NOT LIKE '% %';

SELECT title 
FROM track 
WHERE LOWER(title) LIKE '%мой%' OR LOWER(title) LIKE '%my%';

SELECT g.name AS genre, COUNT(ag.artist_id) AS artist_count
FROM genre g
LEFT JOIN artist_genre ag ON g.id = ag.genre_id
GROUP BY g.name
ORDER BY artist_count DESC;

SELECT COUNT(t.id) AS track_count
FROM track t
JOIN album a ON t.album_id = a.id
WHERE a.year BETWEEN 2019 AND 2020;

SELECT 
    a.title AS album_title,
    AVG(t.duration) AS avg_duration
FROM 
    album a
JOIN 
    track t ON a.id = t.album_id
GROUP BY 
    a.id, a.title
ORDER BY 
    a.title;
    
SELECT ar.name AS artist
FROM artist ar
WHERE ar.id NOT IN (
    SELECT aa.artist_id
    FROM artist_album aa
    JOIN album al ON aa.album_id = al.id
    WHERE al.year = 2020
);

SELECT DISTINCT c.title AS compilation
FROM collection c
JOIN collection_track ct ON c.id = ct.collection_id
JOIN track t ON ct.track_id = t.id
JOIN album a ON t.album_id = a.id
JOIN artist_album aa ON a.id = aa.album_id
JOIN artist ar ON aa.artist_id = ar.id
WHERE ar.name = 'Queen'
ORDER BY c.title;

SELECT DISTINCT a.title AS album_title
FROM album a
JOIN artist_album aa ON a.id = aa.album_id
JOIN artist ar ON aa.artist_id = ar.id
JOIN artist_genre ag ON ar.id = ag.artist_id
GROUP BY a.id, a.title, ar.id
HAVING COUNT(DISTINCT ag.genre_id) > 1;

SELECT t.title AS track_title
FROM track t
LEFT JOIN collection_track ct ON t.id = ct.track_id
WHERE ct.track_id IS NULL;

SELECT ar.name AS artist_name
FROM artist ar
JOIN artist_album aa ON ar.id = aa.artist_id
JOIN album a ON aa.album_id = a.id
JOIN track t ON a.id = t.album_id
WHERE t.duration = (SELECT MIN(duration) FROM track);

SELECT a.title AS album_title, COUNT(t.id) AS track_count
FROM album a
JOIN track t ON a.id = t.album_id
GROUP BY a.id, a.title
HAVING COUNT(t.id) = (
    SELECT COUNT(t2.id)
    FROM album a2
    JOIN track t2 ON a2.id = t2.album_id
    GROUP BY a2.id
    ORDER BY COUNT(t2.id)
    LIMIT 1
);