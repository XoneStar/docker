/* 
	lib_mysqludf_json - a library of mysql udfs to map data to JSON format
	Copyright (C) 2007  Roland Bouman 
	web: http://www.xcdsql.org/MySQL/UDF/ 
	email: mysqludfs@gmail.com
	
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.
	
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
drop function lib_mysqludf_json_info;
drop function json_array;
drop function json_members;
drop function json_object;
drop function json_values;

create function lib_mysqludf_json_info returns string soname 'lib_mysqludf_json.so';
create function json_array returns string soname 'lib_mysqludf_json.so';
create function json_members returns string soname 'lib_mysqludf_json.so';
create function json_object returns string soname 'lib_mysqludf_json.so';
create function json_values returns string soname 'lib_mysqludf_json.so';

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

/*
    Create the libmysqludf_humanage libmysqludf_urlencode UDF function in the MySQL
*/
create function humanage;
create function urlencode;

create function humanage returns string soname 'libmysqludf_humanage.so';
create function urlencode returns string soname 'libmysqludf_urlencode.so';
create function urldecode returns string soname 'libmysqludf_urldecode.so';