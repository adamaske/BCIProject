#include "pch.h"
#include "Network.h"
#include "Layer.h"

Network::Network()
{
	Logger::Log("Network created");
}

void Network::SetupNetwork(std::vector<Layer*> layers)
{
	mLayers = layers;

	for (auto layer : mLayers) {
		//
		layer->PopulateRandom();
	}
}
void Network::SetupNetwork(std::vector<float> layerSizes)
{
	for (int i = 0; i < layerSizes.size(); i++)
	{
		//The first layer size is not treated as a node, only a connectino
		Layer* layer = new Layer(layerSizes[i + 1], layerSizes[i]);
	}
}


std::vector<float> Network::Output(std::vector<float> input)
{
	std::vector<float> output;

	for (int i = 0; i < mLayers.size(); i++) {
		output = mLayers[i]->Output(input);
	}

	return output;
}

std::vector<float> Network::Output(std::vector<float> input, std::vector<float> correctOutput)
{
	//Gets the output
	auto output = Output(input);

	//Vector to store the costs
	std::vector<float> costs;
	costs.reserve(output.size());

	//We want the correctOutput(n) - output(n)
	for (int i = 0; i < output.size(); i++) {
		costs[i] = output[i] - correctOutput[i];
	}

	//Squares them, no negative numbers iguess
	std::vector<float> costsSquared = costs;
	//The total cost from the output layer
	float totalCost = 0;
	for (auto i = 0; i < costsSquared.size(); i++)
	{
		costsSquared[i] = pow(costsSquared[i], 2);
		totalCost += costsSquared[i];
	}
	//This vector should now be possible to graph
	mTotalCosts.push_back(totalCost);
	//how do we find the derivative of the errorfunction

	std::vector<float> slopes;
	slopes.reserve(costs.size());

	for (int i = 0; i < slopes.size(); i++) {
		//Derivative of the activation function Activation =( Activation - Cost )^2
		slopes[i] = 2 * (output[i] - correctOutput[i]);
		//this gives a vector of the gradients
		//this slopes vector can now be used for correcting the guesses
		//newSlope/newGuess/newWeight?? = currentWeight - (learningRate * 2(Ouput - Input))
	};

	//We want to go backwards in the layers
	//the layers are in order, 0 is the first/input layer, size-1 is the outputlayer
	auto outputLayer = mLayers[mLayers.size() - 1];
	//We can now use these costs, which should equal in number to the output of the outputlayer
	//We should loop over all the weights in the output layer, and every bias, using a different function
	float learningRate = 0.01f;
	for (int node = 0; node < outputLayer->mNodes; node++) {
		for (int connection = 0; node < outputLayer->mConnections; connection++) {

			outputLayer->mWeights[(node * connection) + connection] =
				outputLayer->mWeights[(node * connection) + connection] - 
				(learningRate * (2 * outputLayer->mOutputs[node] - correctOutput[node]));
		}
	}
	//this only applies to the outputlayer, for further backprop we need more calculation
	//the weights connected to each of the outputlayer nodes should be corrected
	//we now have a bunch of differences between the output and the desired output, We can now find the gradient of the decent

	return costs;
}

void Network::PrintNetwork()
{
	Logger::Log("Network Starting Print");
	int i = 0;
	for (auto layer : mLayers) {
		std::cout << "Layer : " << i << "\n";
		int w = 0;
		for (auto weight : layer->mWeights) {
			std::cout << "w" << w << "( " << weight << " ), ";
			w++;
		}
		std::cout << "\n";
		int b = 0;
		for (auto bias : layer->mBiases) {
			std::cout << "b" << b << "( " << bias << "), ";
			b++;
		}
		std::cout << "\n";
		i++;
	}
}