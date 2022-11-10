# ui_server_client_test

### Build
To build both server and client use:
```
git pull https://github.com/pivovard/ui_server_client_test.git
cmake .
make
```

### Server
```
./ui_server/ui_server [port]
```
Default port is 5001.

### Client
```
./ui_client/ui_client [ip_addr] [port]
```
Default address is localhost, port is 5001.

#### Commands:
- cpu - returns cpu usage
- mem - returns mem usage
- exit - disconnect from the server and exit the client
