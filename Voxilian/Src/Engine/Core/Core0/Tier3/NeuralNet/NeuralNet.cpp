#include "NeuralNet.h"
#include "..\..\Core0.h"

CNNNode::CNNNode()
{
	value=0.0f;
}
void CNETINIT(CNeuralNet* net)
{
}
void CNeuralNet::Init(int iiinputs,int iiwidth,int iiheight,int iioutputs)
{
	iinputs=iiinputs;
	iwidth=iiwidth;
	iheight=iiheight;
	ioutputs=iioutputs;
	inputs.resize(iinputs);
	nodes.resize(iwidth);
	outputs.resize(ioutputs);
	targets.resize(ioutputs);
	target.resize(ioutputs);
	for(int i = 0;i<iinputs;i++)
	{
		CNNNode* cn = new CNNNode();
		cn->weights.resize(iheight);
		for(int j = 0;j<iheight;j++)
		{
			cn->weights[j]=rnd();
		}
		inputs[i]=cn;
	}
	for(int i = 0;i<iwidth;i++)
	{
		nodes[i].resize(iheight);
		for(int j = 0;j<iheight;j++)
		{
			CNNNode* cn = new CNNNode();
			cn->weights.resize(iheight);
			for(int k = 0;k<iheight;k++)
			{
				cn->weights[k]=rnd();
			}
			nodes[i][j]=cn;
		}
	}
	for(int i = 0;i<ioutputs;i++)
	{
		CNNNode* cn = new CNNNode();
		outputs[i]=cn;
		target[i]=false;
		targets[i]=0.0f;
	}
}
void CNETRUN(CNeuralNet* net)
{
	net->Calculate();
	net->BackPropagate();
}
void CNeuralNet::Run()
{
	if(glfwWaitThread(thread,GLFW_NOWAIT)==1)
	{
		thread = glfwCreateThread((GLFWthreadfun)CNETRUN,this);
	}
}
float sigmoid(float num)
{
	return (1.0f/(powf(EXP,num)));
}
void CNeuralNet::Calculate()
{
	for(int i = 0;i<iwidth;i++)
	{
		for(int j = 0;j<iheight;j++)
		{
			float value = 0.0f;
			if(i==0)
			{
				for(int k = 0;k<iinputs;k++)
				{
					value+=inputs[k]->value*inputs[k]->weights[j];
				}
			}
			else
			{
				for(int k = 0;k<iheight;k++)
				{
					value+=nodes[i-1][k]->value*nodes[i-1][k]->weights[j];
				}
			}
			nodes[i][j]->value=sigmoid(value);
		}
	}
}
void CNeuralNet::BackPropagate()
{
}