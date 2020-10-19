#!/bin/sh
user="dorian.vinai"
key_path="~/.ssh/epita"

ports=(22502 22503 22504 22508 22509 22505 22506 22507 22512 22513 22514 22515 22517 22510 22518 22520 22519 22521)
port=${ports[$RANDOM % ${#ports[@]} ]}
echo "port: $port"
ssh -X -l "$user" -p $port -i "$key_path" -o StrictHostKeyChecking=no gate.cri.epita.fr
