CREATE TABLE IF NOT EXISTS Artist (
	id SERIAL PRIMARY KEY,
	name VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS Genre (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS Artist_Genre (
    artist_id INT NOT NULL REFERENCES Artist(id),
    genre_id INT  NOT NULL REFERENCES Genre(id),
    CONSTRAINT pk PRIMARY KEY (artist_id, genre_id)
);

CREATE TABLE IF NOT EXISTS Album (
    id SERIAL PRIMARY KEY,
    title VARCHAR(100) NOT NULL,
    year INT NOT NULL
);

CREATE TABLE IF NOT EXISTS Artist_Album (
    artist_id INT  NOT NULL REFERENCES Artist(id),
    album_id INT  NOT NULL REFERENCES Album(id),
    CONSTRAINT pk_1 PRIMARY KEY (artist_id, album_id)
);

CREATE TABLE IF NOT EXISTS Track (
    id SERIAL PRIMARY KEY,
    title VARCHAR(100) NOT NULL,
    duration TIME NOT NULL,
    album_id INT REFERENCES Album(id)
);

CREATE TABLE IF NOT EXISTS Collection (
    id SERIAL PRIMARY KEY,
    title VARCHAR(100) NOT NULL,
    year INT NOT NULL
);

CREATE TABLE IF NOT EXISTS Collection_Track (
    collection_id INT REFERENCES Collection(id),
    track_id INT  NOT NULL REFERENCES Track(id),
    CONSTRAINT pk_2 PRIMARY KEY (collection_id, track_id)
);