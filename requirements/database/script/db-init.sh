service mariadb start;
#environement variables will be passed through a .env file
mysql -e "CREATE DATABASE IF NOT EXISTS \`${SQL_DATABASE}\`;"
# echo "1"
mysql -e "USE \`${SQL_DATABASE}\`;"
# echo "2"
mysql -e "CREATE TABLE IF NOT EXISTS TICKETS (
	ticketsID INT AUTO INCREMENT UNIQUE NOT NULL,
	channelID INT UNIQUE NOT NULL,
	userID INT NOT NULL,
	logFile VARCHAR(32) NOT NULL,
	PRIMARY KEY(ticketsID)
	);"

	mysql -e "CREATE TABLE IF NOT EXISTS ATTACHMENTS (
    attachmentID INT AUTO INCREMENT UNIQUE NOT NULL,
    attachementFilename VARCHAR(32),
    ticketsID INT REFERENCES TICKETS.ticketsID,
    PRIMARY KEY(attachmentID),
);"
# echo "3"
mysql -e "CREATE USER IF NOT EXISTS \`${SQL_USER}\`@'localhost' IDENTIFIED BY '${SQL_PASSWORD}';"
# echo "4"
#identifie l'utilisateur créé juste avant comme l'administrateur
mysql -e "GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO \`${SQL_USER}\`@'%' IDENTIFIED BY '${SQL_PASSWORD}';"
mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}';"
mysql -e "FLUSH PRIVILEGES;"
sleep 1;
mysqladmin -u root shutdown
exec mysqld_safe