-- 1、练习创建数据库，创建表操作
-- 创建数据库
create database test;
use test;
-- 创建表
create table Person(personID int not NULL auto_increment,primary key(personID),FirstName varchar(15),LastName varchar(15),Age int);
-- 查看所有表
show tables;
-- 查看表创建信息
show create table Person;
-- 查看表内容
select * from Person;
-- 增加表内容
alter table Person add birthday DATE;
alter table Person add addr varchar(15) NOT NULL;
-- 删除表内容
alter table Person drop addr;


-- 2、练习单表的增删查改操作，distinct，order by，limit操作
-- 增加行内容
insert into Person(personID,FirstName,LastName,Age,birthday) values(0,'yang','yijia',22,'1999-10-16');-- 记得用单引号包住字符和日期时间
insert into Person(personID,FirstName,LastName,Age,birthday) values(0,'zhang','san',21,'2000-9-15');
insert into Person(personID,FirstName,LastName,Age,birthday) values(0,'li','si',20,'2001-8-14');
insert into Person(personID,FirstName,LastName,Age,birthday) values(0,'wang','wu',19,'2002-7-13');
insert into Person(personID,FirstName,LastName,Age,birthday) values(0,'yang','guo',22,'1999-7-13');
insert into Person(personID,FirstName,LastName,Age,birthday) values(0,'wang','gang',19,'2002-7-13');
-- 删除行内容
delete from Person where Age=23;
-- 查找行内容
select FirstName Surname,LastName from Person where Age=22;
select FirstName Surname,LastName,Age+8 from Person order by Age;
select FirstName Surname,LastName,Age from Person order by Age desc limit 0,3;-- 从第0条开始的3条
select FirstName Surname,LastName from Person where Age=22;
-- 子查询
select * from Person where personID=(select personID from Person where birthday Like '1999-10%');
-- 更改行内容
update Person set LastName='lei' where Age=20;


-- 3、练习Person和pets表的关联查询操作，包括内连接，左连接，右连接
-- 学习外键
create table pets(petID int NOT NULL AUTO_INCREMENT,PRIMARY KEY(petId),`name` varchar(20),personID int default NULL,FOREIGN KEY (personID) REFERENCES Person(personID));
insert into pets(petID,name,personID) values(0,'dog',6);
insert into pets(petID,name,personID) values(0,'cat',5);
insert into pets(petID,name,personID) values(0,'cat',6);
insert into pets(petID,name,personID) values(0,'hawk',12);
select * from pets;
show create table pets;
-- 删除外键
alter table pets drop FOREIGN KEY pets_ibfk_1;
-- 增加外键
alter table pets add FOREIGN KEY pets_ibfk_2(personID) references Person(personID);
-- 显式内连接
select * from pets p inner join Person m on p.personID=m.personID;
-- 左外连接
select * from pets p left join Person m on p.personID=m.personID;
select * from Person m left join pets p on p.personID=m.personID;-- Person在左边就代表要把Person全部显示出来
-- 右连接
select * from Person m right join pets p on p.personID=m.personID;
select * from pets p right join Person m on p.personID=m.personID;-- Person在右边就代表要把Person全部显示出来
-- 多对多操作
create table TEACHER(ID int primary key,NAME varchar(100));
insert into TEACHER values(1,'math teacher'),(2,'chinese teacher'),(3,'english teacher');
create table STUDENT(ID int primary key,NAME varchar(100));
insert into STUDENT values(1,"lily");
insert into STUDENT values(2,"lucy");
insert into STUDENT values(3,"lilei");
insert into STUDENT values(4,"lilyzhou");
create table TEACHER_STUDENT(T_ID int,S_ID int,primary key(T_ID,S_ID),constraint T_ID_FK foreign key(T_ID) references TEACHER(ID),constraint S_ID_FK foreign key(S_ID) references STUDENT(ID));
insert into TEACHER_STUDENT VALUES(1,1);


-- 4、练习group by，having，5个统计函数的操作
select * from Person where Age=22;
select * from Person where Age<>22;
select * from Person where Age between 22 and 24;
-- group by
select count(Age),Age,max(birthday) from Person group by Age;
-- having
select count(Age) as num,Age,max(birthday) from Person group by Age HAVING num=1;
-- 统计函数
select count(Age),sum(Age),max(Age),min(Age),avg(Age),Age,max(birthday) from Person group by Age;


-- 5、学会备份数据库，还原数据库
-- mysqldump -u root -p test>test.sql
-- mysql -u root -p test<test.sql