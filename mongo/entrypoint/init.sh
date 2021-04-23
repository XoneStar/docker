#!/bin/bash

mongo <<EOF
use admin;
db.createUser({user:"root", pwd:"root", roles:[{"role": "root", "db":"admin"}]});

use waf;
db.createUser({user:"admin", pwd:"admin", roles:[{"role": "readWrite", "db":"db_name"}]});

EOF
