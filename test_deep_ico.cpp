#include "deep_ico.h"
#include <Iir.h>
#include<stdio.h>

void test_forward() {
	Deep_ICO* deep_ico = new Deep_ICO(2,2);
	FILE* f=fopen("test_forward.dat","wt");

	deep_ico->hiddenLayer->setInput(0,0);
	deep_ico->hiddenLayer->setInput(1,0);
	deep_ico->setLearningRate(0);
	deep_ico->hiddenLayer->setError(0);
	
	// let's set all weights to zero
	for(int i=0;i<2;i++) {
		for(int j=0;j<2;j++) {
			deep_ico->hiddenLayer->neurons[i]->weights[j]=0;
			deep_ico->outputLayer->neurons[i]->weights[j]=0;
		}
	}

	for(int n = 0; n < 100;n++) {
		
		float stim = 0;
		if ((n>10)&&(n<20)) {
			stim = -1;
		}
		deep_ico->hiddenLayer->setInput(0,stim);
		deep_ico->hiddenLayer->setInput(1,stim);

		fprintf(f,"%f ",stim);

		deep_ico->doStep();

		fprintf(f,"%f ",deep_ico->hiddenLayer->neurons[0]->sum);
		fprintf(f,"%f ",deep_ico->hiddenLayer->neurons[1]->sum);
		fprintf(f,"%f ",deep_ico->outputLayer->neurons[0]->output);
		fprintf(f,"%f ",deep_ico->outputLayer->neurons[1]->output);
		
		fprintf(f,"\n");
		
	}

	fclose(f);
}



void test_learning() {
	Deep_ICO* deep_ico = new Deep_ICO(2,2);
	FILE* f=fopen("test_learning.dat","wt");

	deep_ico->hiddenLayer->setInput(0,0);
	deep_ico->hiddenLayer->setInput(1,0);
	deep_ico->setLearningRate(0.1);
	
	// let's set all weights to one
	for(int i=0;i<2;i++) {
		for(int j=0;j<2;j++) {
			deep_ico->hiddenLayer->neurons[i]->weights[j]=1;
			deep_ico->outputLayer->neurons[i]->weights[j]=1;
		}
	}

	for(int n = 0; n < 1000;n++) {
		
		float stim = 0;
		float err = 0;
		if ((n>10)&&(n<1000)) {
			stim = 1;
			if ((n>500)&&(n<600)) {
				err = 1;
			}
			if ((n>700)&&(n<1000)) {
				err = -1;
			}
		}
		deep_ico->hiddenLayer->setInput(0,stim);
		deep_ico->hiddenLayer->setInput(1,stim);
		deep_ico->hiddenLayer->setError(err);

		fprintf(f,"%f %f ",stim,err);

		deep_ico->doStep();

		for(int i=0;i<2;i++) {
			for(int j=0;j<2;j++) {
				fprintf(f,
					"%f ",
					deep_ico->hiddenLayer->neurons[i]->weights[j]);
			}
		}
		for(int i=0;i<2;i++) {
			for(int j=0;j<2;j++) {
				fprintf(f,
					"%f ",
					deep_ico->outputLayer->neurons[i]->weights[j]);
			}
		}
		for(int i=0;i<2;i++) {
			fprintf(f,
				"%f ",
				deep_ico->outputLayer->neurons[i]->output);
		}
		fprintf(f,"\n");
		
	}

	fclose(f);
}


// what we need is a simple scenario where the trigger of the error
// can be prevented by a predictive signal, for example navigating
// towards a target
// The output is then able to suppress the error by intervening
// what we need first is a control system which diverts from the
// desired state and swings back!

#define IIRORDER 2

void test_closedloop() {
	Deep_ICO* deep_ico = new Deep_ICO(2,2);

	Iir::Bessel::LowPass<IIRORDER> p0;
	p0.setup (IIRORDER,1,0.1);
	
	Iir::Bessel::LowPass<IIRORDER> h0;
	h0.setup (IIRORDER,1,0.1);
	
	FILE* f=fopen("test_closedloop.dat","wt");

	deep_ico->hiddenLayer->setInput(0,0);
	deep_ico->hiddenLayer->setInput(1,0);
	deep_ico->setLearningRate(0.2);

	float v = 0;
	float v0 = 0;
	float x0 = 0;
	float err = 0;
	float dist = 0;
	float pred = 0;
	
	// let's set all weights to zero
	for(int i=0;i<2;i++) {
		for(int j=0;j<2;j++) {
			deep_ico->hiddenLayer->neurons[i]->weights[j]=0;
			deep_ico->outputLayer->neurons[i]->weights[j]=0;
		}
	}

	for(int step = 0; step < 10000; step++) {

		int n = step % 1000;
		
		pred = 0;
		dist = 0;
		if ((n>100)&&(n<1000)) {
			pred = 1;
			if ((n>500)&&(n<800)) {
				dist = 1;
			}
			if ((n>700)&&(n<1000)) {
				dist = 0;
			}
		}
		deep_ico->hiddenLayer->setInput(0,pred);
		deep_ico->hiddenLayer->setInput(1,pred);

		deep_ico->doStep();

		v0 = dist - v;

		for(int i=0;i<2;i++) {
			v0 = v0 + deep_ico->outputLayer->neurons[i]->output;
		}

		x0 = p0.filter(v0);

		float fb_gain = 0.2;

		err = - x0 * fb_gain;
		
		v = h0.filter(err);
		
		deep_ico->hiddenLayer->setError(err);

		fprintf(f,"%d %f %f %f %f %f ",n,pred,dist,err,x0,v0);


		for(int i=0;i<2;i++) {
			fprintf(f,
				"%f ",
				deep_ico->outputLayer->neurons[i]->output);
		}

		for(int i=0;i<2;i++) {
			for(int j=0;j<2;j++) {
				fprintf(f,
					"%f ",
					deep_ico->hiddenLayer->neurons[i]->weights[j]);
			}
		}
		for(int i=0;i<2;i++) {
			for(int j=0;j<2;j++) {
				fprintf(f,
					"%f ",
					deep_ico->outputLayer->neurons[i]->weights[j]);
			}
		}
		fprintf(f,"\n");
		
	}

	fclose(f);
}



int main(int,char**) {
	test_forward();
	test_learning();
	test_closedloop();
}