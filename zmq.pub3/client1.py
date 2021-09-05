#!/usr/bin/env python3
#-*- coding: utf-8 -*-
import zmq

context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.connect("tcp://localhost:5555")
socket.setsockopt(zmq.SUBSCRIBE,''.encode('utf-8'))  # 接收所有消息
while True:
    response = socket.recv().decode('utf-8');
    print("response: %s" % response)
