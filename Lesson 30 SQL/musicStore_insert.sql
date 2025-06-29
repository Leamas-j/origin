INSERT INTO genre (id, name) VALUES
(1, 'Рок'),
(2, 'Поп'),
(3, 'Хип-хоп'),
(4, 'Джаз'),
(5, 'Электроника');

INSERT INTO artist (id, name) VALUES
(1, 'Король и Шут'),
(2, 'Madonna'),
(3, 'Eminem'),
(4, 'Miles Davis'),
(5, 'Daft Punk'),
(6, 'Queen');

INSERT INTO artist_genre (artist_id, genre_id) VALUES
(1, 1), 
(2, 2), 
(3, 3), 
(4, 4),  
(5, 5),  
(5, 2), 
(6, 1),  
(6, 2); 

INSERT INTO album (id, title, year) VALUES
(1, 'Акустический альбом', 1999),
(2, 'Like a Virgin', 1984),
(3, 'The Marshall Mathers LP', 2000),
(4, 'Kind of Blue', 1959),
(5, 'Random Access Memories', 2013),
(6, 'A Night at the Opera', 1975),
(7, 'Madame X', 2019),
(8, 'Music to Be Murdered By', 2020);

INSERT INTO artist_album (artist_id, album_id) VALUES
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(5, 5),
(6, 6),
(2, 7),
(3, 8);

INSERT INTO Track (id, title, duration, album_id) VALUES
(1, 'Лесник', '3:33', 1),
(2, 'Ели мясо мужики', '3:07', 1),
(3, 'Like a Virgin', '3:40', 2),
(4, 'Material Girl', '4:00', 2),
(5, 'The Real Slim Shady', '4:44', 3),
(6, 'Stan', '6:44', 3),
(7, 'So What', '9:27', 4),
(8, 'Freddie Freeloader', '7:36', 4),
(9, 'Get Lucky', '6:09', 5),
(10, 'Instant Crush', '5:37', 5),
(11, 'Bohemian Rhapsody', '5:54', 6),
(12, 'Love of My Life', '3:39', 6),
(13, 'You are My Best Friend', '2:52', 6),
(14, 'Premonition', '2:54', 8),
(15, 'In Too Deep', '3:15', 8),
(16, 'Dark Ballet', '4:14', 7),
(17, 'Come Alive', '4:02', 7);

INSERT INTO collection (id, title, year) VALUES
(1, 'Лучшие рок-хиты', 2010),
(2, 'Поп-музыка 80-х', 2005),
(3, 'Хип-хоп антология', 2015),
(4, 'Джазовые стандарты', 2000),
(5, 'Электронная вечеринка', 2018),
(6, 'Легенды музыки', 2020);


INSERT INTO collection_track (collection_id, track_id) VALUES
(1, 1),  
(1, 2),
(1, 11), 
(1, 12),
(2, 3),  
(2, 4),
(2, 9),  
(3, 5),   
(3, 6),
(4, 7),   
(4, 8),
(5, 9),  
(5, 10),
(6, 11),  
(6, 12),
(6, 13),
(6, 1);   