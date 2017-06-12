import deep_ico
import numpy as np

# We do backprop of the error with traditional backprop
def testBackprop():
    with open('test_bp_py.csv', 'wb') as csvfile:
        csvfile.close()
        
    with open('test_bp_py.csv', 'ab') as csvfile:
        # two input neurons, two hidden ones and one output neuron
        net = deep_ico.Deep_ICO(2, 2, 1)
        # init the weights
        net.initWeights(0.1);
        net.setAlgorithm(deep_ico.Deep_ICO.backprop);
        # create the input arrays in numpy fashion
        inp = np.zeros(2)
        err = np.zeros(1)
        for i in range(100):
            if (i > 10) :
                inp[0] = 1
            else :
                inp[0] = 0
            if ((i > 20) and (i<90)) :
                err[0] = 1
            else :
                err[0] = 0
            # does both forward propagation and backpropagation
            net.doStep(inp,err)
            # gets the output of the output neuron
            output = net.getOutput(0)
            print(output)
            np.savetxt(csvfile,np.hstack((inp,err,output)),delimiter="\t",newline="\t")
            crlf="\n"
            csvfile.write(crlf.encode())


# We do backprop of the error with traditional backprop
def testBackpropWithFilters():
    print("testBackpropWithFilters")
    with open('test_bp_filt_py.csv', 'wb') as csvfile:
        csvfile.close()
        
    with open('test_bp_filt_py.csv', 'ab') as csvfile:
        # two input neurons, two hidden ones and one output neuron
        # two filters and min temp filter is 10 pixels and max 100 pixels
        nFiltersInput = 10
        nFiltersHidden = 10
        # nFiltersHidden = 0 means that the layer is linear without filters
        minT = 1000
        maxT = 10000
        net = deep_ico.Deep_ICO(2, 2, 1, nFiltersInput, nFiltersHidden, minT,maxT)
        # init the weights
        net.initWeights(0.1);
        net.setAlgorithm(deep_ico.Deep_ICO.backprop);
        # create the input arrays in numpy fashion
        inp = np.zeros(2)
        err = np.zeros(1)
        for i in range(1000):
            if ((i > 100) and (i<103)):
                inp[0] = 1
            else :
                inp[0] = 0
            if ((i > 110) and (i<120)) :
                err[0] = 1
            else :
                err[0] = 0
            # does both forward propagation and backpropagation
            net.doStep(inp,err)
            # gets the output of the output neuron
            output = net.getOutput(0)
            print(output)
            np.savetxt(csvfile,np.hstack((inp,err,output)),delimiter="\t",newline="\t")
            crlf="\n"
            csvfile.write(crlf.encode())


# we do forward propagation of the error from the inputs as
# done in ICO learning but now with a hidden layer
# note: all weights can be zero initially and will grow then!
def testICO():
    with open('test_ico_py.csv', 'wb') as csvfile:
        csvfile.close()
        
    with open('test_ico_py.csv', 'ab') as csvfile:
        # two input neurons, two hidden ones and one output neuron
        net = deep_ico.Deep_ICO(2, 2, 1)
        net.setAlgorithm(deep_ico.Deep_ICO.ico);
        # create the input arrays in numpy fashion
        inp = np.zeros(2)
        err = np.zeros(1)
        for i in range(100):
            if (i > 10) :
                inp[0] = 1
            else :
                inp[0] = 0
            if ((i > 20) and (i<90)) :
                err[0] = 1
            else :
                err[0] = 0
            # does both forward propagation and backpropagation
            net.doStep(inp,err)
            # gets the output of the output neuron
            output = net.getOutput(0)
            print(output)
            np.savetxt(csvfile,np.hstack((inp,err,output)),delimiter="\t",newline="\t")
            crlf="\n"
            csvfile.write(crlf.encode())

# we do forward propagation of the error from the inputs as
# done in ICO learning but now with a hidden layer
# note: all weights can be zero initially and will grow then!
def testICOwithFilters():
    with open('test_ico_py.csv', 'wb') as csvfile:
        csvfile.close()
        
    with open('test_ico_py.csv', 'ab') as csvfile:
        # two input neurons, two hidden ones and one output neuron
        # two filters and min temp filter is 10 pixels and max 100 pixels
        nFiltersInput = 10
        nFiltersHidden = 10
        # nFiltersHidden = 0 means that the layer is linear without filters
        minT = 10
        maxT = 100
        net = deep_ico.Deep_ICO(2, 2, 1, nFiltersInput, nFiltersHidden, minT,maxT)
        net.setAlgorithm(deep_ico.Deep_ICO.ico);
        net.initWeights(0.1);
        net.setLearningRate(10);
        # create the input arrays in numpy fashion
        inp = np.zeros(2)
        err = np.zeros(1)
        for i in range(200):
            if ((i > 10) and (i<15)) :
                inp[0] = 1
            else :
                inp[0] = 0
            if ((i > 20) and (i<30)) :
                err[0] = 1
            else :
                err[0] = 0
            # does both forward propagation and backpropagation
            # print('err1=',err);
            net.doStep(inp,err)
            # gets the output of the output neuron
            output = net.getOutput(0)
            print(inp[0],err[0],output);
            np.savetxt(csvfile,np.hstack((inp[0],err[0],output)),delimiter="\t",newline="\t")
            crlf="\n"
            csvfile.write(crlf.encode())

# testBackpropWithFilters()
# testBackprop()
# testICO()
testICOwithFilters()
