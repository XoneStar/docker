/*
    Create the mysql-udf-http UDF function in the MySQL
*/
drop function http_get;
drop function http_post;
drop function http_put;
drop function http_delete;

create function http_get returns string soname 'mysql-udf-http.so';
create function http_post returns string soname 'mysql-udf-http.so';
create function http_put returns string soname 'mysql-udf-http.so';
create function http_delete returns string soname 'mysql-udf-http.so';
