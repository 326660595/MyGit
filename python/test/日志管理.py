import logging

# 配置日志输出到文件
log_file = 'path/to/log/file.log'  # 替换为要输出日志的文件路径
logging.basicConfig(filename=log_file, level=logging.DEBUG,
                    format='%(asctime)s - %(levelname)s - %(message)s')

# 示例日志输出
logging.debug('这是一条调试信息')
logging.info('这是一条信息')
logging.warning('这是一条警告')
logging.error('这是一条错误')
