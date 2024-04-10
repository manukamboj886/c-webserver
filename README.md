# c++-webserver

To run the web server files in Fedora Linux, you'll need to follow these general steps:

Install Required Dependencies Before running the web server, you'll need to ensure that all the necessary dependencies are installed. This typically includes a C++ compiler, make utility, and any required libraries or frameworks used by the web server. You can install the basic build essentials on Fedora with the following command:


sudo dnf groupinstall "Development Tools" "Development Libraries"
If your web server requires additional libraries or frameworks, you'll need to install them as well. For example, if you're using the Boost C++ libraries, you can install them with:<br/>


sudo dnf install boost-devel<br/>
Build the Web Server Once you have all the required dependencies installed, you can build the web server from its source code. Typically, this involves running the following commands from the root directory of the source code:

<br/>
mkdir build
cd build
cmake ..
make<br/>
The cmake command generates the build files based on the project's configuration. The make command then compiles the source code and links the resulting object files into the final executable.
Run the Web Server After successfully building the web server, you can run the resulting executable. The exact command to run the executable will depend on the structure and configuration of your web server project. Assuming your web server executable is named webserver and is located in the build directory, you can run it with:

<br/>
./build/webserver<br/>
You may need to provide additional command-line arguments or configuration files to specify the server's IP address, port, document root directory, or other settings.
Configure Firewall (Optional) If your web server listens on a specific port (e.g., 80 for HTTP or 443 for HTTPS), you may need to configure the firewall on your Fedora system to allow incoming connections on that port. You can check the current firewall configuration with:

<br/>
sudo firewall-cmd --list-all<br/>
To allow incoming connections on a specific port (e.g., 8080), you can run:

<br/>
sudo firewall-cmd --permanent --add-port=8080/tcp<br/>
sudo firewall-cmd --reload<br/>
Replace 8080 with the appropriate port number for your web server.
Test the Web Server Once the web server is running, you can test it by accessing it from a web browser on the same machine or from a different computer on the same network. If your web server is listening on localhost or 127.0.0.1, you can access it from the same machine using http://localhost:<port> or http://127.0.0.1:<port>, replacing <port> with the appropriate port number. If your web server is configured to listen on a specific IP address, you can access it from other computers on the same network using http://<ip_address>:<port>, replacing <ip_address> with the IP address of the machine running the web server.
