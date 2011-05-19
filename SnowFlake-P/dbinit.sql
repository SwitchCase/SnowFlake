drop database if exists onj2;
create database onj2;
use onj;

DROP TABLE IF EXISTS users;


create table users
(
	id int auto_increment,
	username varchar(50) unique not null,
	password varchar(50) not null,
	member1  varchar(50) default null,
	member2 varchar(50) default null,
	member3 varchar(50) default null,
	college varchar(50) default null,
	rank int default 0,
	score int default 0,
	primary key(id)
);

DROP TABLE IF EXISTS submissions;

create table submissions 
( 
	id int auto_increment, 
	userid int, 
	problemid int,
	status int, 
	time int, 
	exec varchar(100),
	primary key(id), 
	constraint FK1 foreign key(userid) references users(id) on delete cascade on update cascade
);


create view scores as
(
select rank, username, score from users U left outer join submissions on U.id = submissions.userid where (score>0 and status=0 and time=(select max(time) from submissions where status=0 and userid=U.id)) or (score=0 and ((select count(*) from submissions where userid=U.id)=0 or (time = (select max(time) from submissions where userid=U.id)))) order by score desc, time asc, username asc
);

DROP TABLE IF EXISTS chat;


create table chat
(
	id int auto_increment,
	userid int,
	time int,
	msg varchar(250),
	primary key(id),
	constraint FK2 foreign key(userid) references users(id) on delete cascade on update cascade
);



DROP TABLE IF EXISTS announcements;


create table announcements
(
	id int auto_increment,
	time int,
	msg varchar(500),
	primary key(id)
);


-- Create admins (rank==1 means admin)
insert into users(username, password, rank) values('admin', 'creative', 1);

