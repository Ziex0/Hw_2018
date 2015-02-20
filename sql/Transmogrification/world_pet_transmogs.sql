/*
Navicat MySQL Data Transfer

Source Server         : Local
Source Server Version : 50612
Source Host           : localhost:3306
Source Database       : 2world

Target Server Type    : MYSQL
Target Server Version : 50612
File Encoding         : 65001

Date: 2013-10-27 13:03:40
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `pet_transmogs`
-- ----------------------------
DROP TABLE IF EXISTS `pet_transmogs`;
CREATE TABLE `pet_transmogs` (
  `id` int(10) unsigned NOT NULL,
  `name` varchar(50) NOT NULL DEFAULT '',
  `price` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of pet_transmogs
-- ----------------------------
INSERT INTO `pet_transmogs` VALUES ('441', '1', '1');
INSERT INTO `pet_transmogs` VALUES ('3275', '2', '1');
INSERT INTO `pet_transmogs` VALUES ('31853', '18', '1');
INSERT INTO `pet_transmogs` VALUES ('31881', '17', '1');
INSERT INTO `pet_transmogs` VALUES ('31892', '16', '1');
INSERT INTO `pet_transmogs` VALUES ('31952', '15', '1');
INSERT INTO `pet_transmogs` VALUES ('31953', '14', '1');
INSERT INTO `pet_transmogs` VALUES ('31956', '13', '1');
INSERT INTO `pet_transmogs` VALUES ('31958', '12', '1');
INSERT INTO `pet_transmogs` VALUES ('31962', '11', '1');
INSERT INTO `pet_transmogs` VALUES ('31992', '10', '1');
INSERT INTO `pet_transmogs` VALUES ('32031', '9', '1');
INSERT INTO `pet_transmogs` VALUES ('32104', '8', '1');
INSERT INTO `pet_transmogs` VALUES ('32105', '7', '1');
INSERT INTO `pet_transmogs` VALUES ('32106', '6', '1');
INSERT INTO `pet_transmogs` VALUES ('32179', '5', '1');
INSERT INTO `pet_transmogs` VALUES ('32670', '4', '1');
INSERT INTO `pet_transmogs` VALUES ('32754', '3', '1');
