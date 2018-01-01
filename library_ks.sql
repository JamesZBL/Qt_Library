/*
Navicat MySQL Data Transfer

Source Server         : 阿里云_MySQL
Source Server Version : 50621
Source Host           : 47.93.187.44:3306
Source Database       : library_ks

Target Server Type    : MYSQL
Target Server Version : 50621
File Encoding         : 65001

Date: 2018-01-01 10:02:21
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for tb_book
-- ----------------------------
DROP TABLE IF EXISTS `tb_book`;
CREATE TABLE `tb_book` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT '',
  `number` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10037 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tb_book
-- ----------------------------
INSERT INTO `tb_book` VALUES ('10001', '三国演义', '55');
INSERT INTO `tb_book` VALUES ('10002', '红楼梦', '221');
INSERT INTO `tb_book` VALUES ('10003', '水浒传', '299');
INSERT INTO `tb_book` VALUES ('10004', '西游记', '229');
INSERT INTO `tb_book` VALUES ('10005', 'Java 从入门到精通', '233');
INSERT INTO `tb_book` VALUES ('10024', '计算机网络', '19');
INSERT INTO `tb_book` VALUES ('10025', '数据结构', '5000');
INSERT INTO `tb_book` VALUES ('10033', '设计模式-可复用面向对象软件的基础', '30');
INSERT INTO `tb_book` VALUES ('10034', '重构-改善既有代码的设计', '50');
INSERT INTO `tb_book` VALUES ('10035', 'Effective Java', '55');
INSERT INTO `tb_book` VALUES ('10036', 'Java 编程思想', '60');

-- ----------------------------
-- Table structure for tb_lend
-- ----------------------------
DROP TABLE IF EXISTS `tb_lend`;
CREATE TABLE `tb_lend` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `book_id` bigint(11) NOT NULL,
  `reader_id` bigint(20) NOT NULL,
  `lend_number` int(11) DEFAULT NULL,
  `is_back` tinyint(2) DEFAULT '0',
  PRIMARY KEY (`id`,`book_id`,`reader_id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tb_lend
-- ----------------------------
INSERT INTO `tb_lend` VALUES ('1', '10001', '15000', '1', '1');
INSERT INTO `tb_lend` VALUES ('2', '10001', '15000', '1', '1');
INSERT INTO `tb_lend` VALUES ('3', '10001', '15000', '1', '1');
INSERT INTO `tb_lend` VALUES ('4', '10001', '15000', '1', '1');
INSERT INTO `tb_lend` VALUES ('5', '10001', '15000', '1', '1');
INSERT INTO `tb_lend` VALUES ('11', '10025', '18333298410', '1', '0');

-- ----------------------------
-- Table structure for tb_reader
-- ----------------------------
DROP TABLE IF EXISTS `tb_reader`;
CREATE TABLE `tb_reader` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `code` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=150008 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tb_reader
-- ----------------------------
INSERT INTO `tb_reader` VALUES ('150001', '李明', '15000');
INSERT INTO `tb_reader` VALUES ('150002', '小红', '15001');
INSERT INTO `tb_reader` VALUES ('150007', '郑保乐', '18333298410');
