-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               10.4.24-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win64
-- HeidiSQL Version:             12.0.0.6468
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Dumping database structure for finiteautomata
CREATE DATABASE IF NOT EXISTS `finiteautomata` /*!40100 DEFAULT CHARACTER SET utf8mb4 */;
USE `finiteautomata`;

-- Dumping structure for table finiteautomata.fa
CREATE TABLE IF NOT EXISTS `fa` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `label` varchar(255) NOT NULL,
  `Q` varchar(255) NOT NULL,
  `StartState` varchar(255) NOT NULL,
  `FinalState` varchar(255) NOT NULL,
  `charactor` varchar(50) NOT NULL,
  `Transition` text NOT NULL,
  `description` text DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4;

-- Dumping data for table finiteautomata.fa: ~8 rows (approximately)
INSERT INTO `fa` (`id`, `label`, `Q`, `StartState`, `FinalState`, `charactor`, `Transition`, `description`) VALUES
	(1, 'My NFA 001', 'q0,q1,q2,q3', 'q0', 'q3', 'ab', 'q0,a:q0,q1#q0,b:q0#q0,¬:¬#q1,a:¬#q1,b:q2#q1,¬:¬#q2,a:¬#q2,b:q3#q2,¬:¬#q3,a:q3#q3,b:q3#q3,¬:¬', 'L={w|w contains abb},X={a,b}'),
	(4, 'NFA 004', 'q0,q1,q2', 'q0', 'q2', '01', 'q0,0:q0#q0,1:q1#q0,¬:¬#q1,0:q1,q2#q1,1:q1#q1,¬:¬#q2,0:q2#q2,1:q1,q2#q2,¬:¬', ''),
	(6, 'MY NFA 004', 'q0,q2,q3,q4,q5,q6,q7', 'q0', 'q2,q5', '01', 'q0,0:q2,q5#q0,1:q3,q7#q0,¬:¬#q2,0:q2#q2,1:q3#q2,¬:¬#q3,0:q4#q3,1:¬#q3,¬:¬#q4,0:q3#q4,1:q4#q4,¬:¬#q5,0:q5#q5,1:q7#q5,¬:¬#q6,0:q5#q6,1:q7#q6,¬:¬#q7,0:q6#q7,1:q7#q7,¬:¬', ''),
	(7, 'DFA 002', 'q0\',q1\',q2\',q3\',q4\',q5\',q6\',q7\',q8\',q9\',q10\'', 'q0\'', 'q1\',q5\',q8\',q10\'', '01', 'q0\',0:q1\'#q0\',1:q2\'#q1\',0:q1\'#q1\',1:q2\'#q2\',0:q3\'#q2\',1:q4\'#q3\',0:q5\'#q3\',1:q6\'#q4\',0:q7\'#q4\',1:q4\'#q5\',0:q8\'#q5\',1:q4\'#q6\',0:q9\'#q6\',1:q6\'#q7\',0:q10\'#q7\',1:q4\'#q8\',0:q5\'#q8\',1:q6\'#q9\',0:q8\'#q9\',1:q4\'#q10\',0:q10\'#q10\',1:q4\'', ''),
	(8, 'NFA 008', 'q0,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10', 'q0', 'q10', '01', 'q0,0:q0#q0,1:q0,q1#q0,¬:¬#q1,0:q2#q1,1:q2#q1,¬:q2#q2,0:q3#q2,1:q3#q2,¬:q3#q3,0:q4#q3,1:q4#q3,¬:q4#q4,0:q5#q4,1:q5#q4,¬:q5#q5,0:q6#q5,1:q6#q5,¬:q6#q6,0:q7#q6,1:q7#q6,¬:q7#q7,0:q8#q7,1:q8#q7,¬:q8#q8,0:q9#q8,1:q9#q8,¬:q9#q9,0:q10#q9,1:q10#q9,¬:q10#q10,0:¬#q10,1:¬#q10,¬:¬', 'L={w|w at least one of the last ten position of w is 1},X={0,1}'),
	(9, 'MY DFA 001', 'q0\',q1\',q2\',q3\',q4\',q5\',q6\',q7\',q8\',q9\',q10\'', 'q0\'', 'q1\',q2\',q3\',q4\',q5\',q6\',q7\',q8\',q9\',q10\'', '01', 'q0\',0:q0\'#q0\',1:q1\'#q1\',0:q2\'#q1\',1:q1\'#q2\',0:q3\'#q2\',1:q1\'#q3\',0:q4\'#q3\',1:q1\'#q4\',0:q5\'#q4\',1:q1\'#q5\',0:q6\'#q5\',1:q1\'#q6\',0:q7\'#q6\',1:q1\'#q7\',0:q8\'#q7\',1:q1\'#q8\',0:q9\'#q8\',1:q1\'#q9\',0:q10\'#q9\',1:q1\'#q10\',0:q0\'#q10\',1:q1\'', 'L={w|w at least one of the last ten position of w is 1},X={0,1}'),
	(10, 'My NFA 003', 'q0,q1,q2,q3,q4', 'q0', 'q4', 'ab', 'q0,a:q1#q0,b:¬#q0,¬:¬#q1,a:¬#q1,b:q2,q3#q1,¬:¬#q2,a:q2#q2,b:q2,q3#q2,¬:¬#q3,a:q4#q3,b:¬#q3,¬:¬#q4,a:¬#q4,b:¬#q4,¬:¬', ' L={w|w starts with ab and ends in ba},X={a,b}'),
	(11, 'MY DFA 008', 'q0\',q1\',q2\',q3\',q4\',q5\'', 'q0\'', 'q4\'', 'ab', 'q0\',a:q1\'#q0\',b:q2\'#q1\',a:q2\'#q1\',b:q3\'#q2\',a:q2\'#q2\',b:q2\'#q3\',a:q4\'#q3\',b:q3\'#q4\',a:q5\'#q4\',b:q3\'#q5\',a:q5\'#q5\',b:q3\'', ' L={w|w starts with ab and ends in ba},X={a,b}');

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
gcf_dbgcf_db