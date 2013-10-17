#ifndef H_NEURALNET
#define H_NEURALNET

#include "..\..\Globals.h"

class CNNNode
{
public:
	float value;
	vector<float> weights;
	CNNNode();
};
class CNeuralNet
{
public:
	int iinputs;
	int iwidth;
	int iheight;
	int ioutputs;
	vector<CNNNode*> inputs;
	vector<vector<CNNNode*>> nodes;
	vector<CNNNode*> outputs;
	vector<float> targets;
	vector<bool> target;
	int thread;
	void Init(int inputs,int width,int height,int outputs);
	void Run();
	void Calculate();
	void BackPropagate();
};

#endif