=========================================
Feedback closed loop learning library/API
=========================================

The API is identical to the C++ API: `fcl.h`,
`neuron.h` and `layer.h` contain docstrings for
all important calls.

The documentation of all functions can be obtained with::
  >>> import feedback_closedloop_learning as fcl
  >>> help(fcl)

The best way to get started is to download the script
in `tests_py` from:
https://github.com/glasgowneuro/feedback_closed_loop_learning

A full application using the Python API is our vizdoom
agent: https://github.com/glasgowneuro/fcl_demos


API
===

Constructors::

  num_of_inputs: number of inputs in the input layer
  num_of_hidden_neurons_per_layer_array: number of neurons in each layer
  num_hid_layers: number of hidden layer (needs to match with array above)
  num_outputs: number of output in the output layer

  FeedbackClosedloopLearning(
			num_of_inputs,
			num_of_hidden_neurons_per_layer_array,
			_num_hid_layers,
			num_outputs)

  filter number >0 means: filterbank
  filter number = 0 means layer without filters
  num_of_inputs: number of inputs in the input layer
  num_of_hidden_neurons_per_layer_array: number of neurons in each layer
  num_hid_layers: number of hidden layer (needs to match with array above)
  num_outputs: number of output in the output layer
  num_filtersInput: number of filters at the input layer
  num_filtersHidden: number of filters in the hiddel layers (usually zero)
  minT: minimum/first temporal duration of the 1st filter
  maxT: maximum/last temporal duration of the last filter
  FeedbackClosedloopLearning(
			num_of_inputs,
			num_of_hidden_neurons_per_layer_array,
			num_hid_layers,
			num_outputs,
			num_filtersInput,
			num_filtersHidden,
			minT,
			maxT)

			
Performs the simulation step::

  input: Array with the input values
  error: Array of the error signals

  doStep(input, error)

  
Gets the output from one of the output neurons::

  double getOutput(index)

  
Sets globally the learning rate::

  learningRate for all layers and neurons.
  setLearningRate(learningRate)

  
Sets how the learnign rate increases or decreases from layer to layer::

  learningRateDiscountFactor: >1 means higher learning rate in deeper layers

  setLearningRateDiscountFactor(learningRateDiscountFactor)

  
Sets a typical weight decay scaled with the learning rate::

  decay: >0, the larger the faster the decay
  setDecay(double decay)

  
Sets the global momentum for all layers::

  setMomentum(double momentum)

  
Sets the activation function of the Neuron::

  activationFunction: see Neuron.ActivationFunction for the different options
  setActivationFunction(activationFunction);

  
Inits the weights in all layers::

  max: Maximum value of the weights
  initBias: If the bias also should be initialised
  weightInitMethod: see Neuron::WeightInitMethod for the options
  
  initWeights(max = 0.001,
              initBias = 1,
              weightInitMethod = Neuron.MAX_OUTPUT_RANDOM);

		    
Seeds the random number generator::

  seedRandom(s)

	
Sets globally the bias::

  setBias(bias);

	
Returns the number of hidden layers::

  getNumHidLayers()

	
Gets the total number of layers::

  getNumLayers()

  
Gets a pointer to a layer::

  getLayer(i)

  
Gets the output layer::

  getOutputLayer()

  
Returns all Layers::

  getLayers()

  
Saves the whole network::

  bool saveModel(const char* name);

  
Loads the network::

  bool loadModel(const char* name);
