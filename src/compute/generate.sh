#!/bin/bash
protoc-c SGCompute.CS.proto --c_out=.
protoc-c SGCompute.SR.proto --c_out=.
