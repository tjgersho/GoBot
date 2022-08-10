

#include "MetaBrain.hpp"



FactRelevence MetaBrain::getClosestFromNetOut(double netXOut) {
	//Search Brain
	Fact* closestFact = NULL;
	double closestDist = 100000;
	for (auto const& fact : brainRef->facts) {
		auto f = fact.second;
 		double center = f->NetXOut;
		double dist = netXOut - center;

		if (closestDist > std::abs(dist)) {
			closestDist = std::abs(dist);
			closestFact = f.get();
		}
	}
	FactRelevence fr(closestFact, closestDist);
	return fr;
}

FactRelevence MetaBrain::GetBayesNetOutFactProbability(double netXOut)
{
	//Bayes Theorem
	// P(A | B) = (P(B | A) * P(A)) / P(B) 
	// The probablility that the answer is going to be A GIVEN B is equal to the Probabilit
	// of B GIVEN A * the probability of A independently devided b the probability of B independently..

	////Wikipedia   example:  Drug testing

	// Tree diagram illustrating drug testing example.U, Ū, “ + ” and “−” are the events representing user, non - user,
	// positive result and negative result.Percentages in parentheses are calculated.
	// Suppose that a test for using a particular drug is 99 % sensitive and 99 % specific.That is, the test will 
	// produce 99 % true positive results for drug users and 99 % true negative results for non - drug users.Suppose 
	// that 0.5% of people are users of the drug.What is the probability that a randomly selected individual with a positive test is a drug user ?
	
	// P(User|+) = P(+|User)P(User)/P(+)
	// P(User|+) = P(+|User)P(User) / (p(+|User)P(User) + P(+|Non-user)P(Non-user))
	// P(User|+) = (0.99 * 0.005)/(0.99*0.005 + 0.01*0.995)
	// P(User|+) ~= 33.2%

	// Even if an individual tests positive, it is more likely that they do not use the drug than that they do.This is because the number of non - users is large compared 
	// to the number of users.The number of false positives outweighs the number of true positives.For example, if 1000 individuals are tested, there are expected to be 995 non - 
	// users and 5 users.From the 995 non - users, 0.01 × 995 ≃ 10 false positives are expected.From the 5 users, 0.99 × 5 ≈ 5 true positives are expected.Out of 15 positive results, only 5 are genuine.

	// The importance of specificity in this example can be seen by calculating that even if sensitivity is raised to 100 % and specificity remains at 99 % then the probability 
	// of the person being a drug user only rises from 33.2% to 33.4%, but if the sensitivity is held at 99 % and the specificity is increased to 99.5% then 
	// the probability of the person being a drug user rises to about 49.9%.

	// How do we think this can apply to my Brain Model?? 

	//Search Brain

	Fact* closestFact = NULL;
	double closestDist = 100000;
	for (auto const& fact : brainRef->facts) {
		auto f = fact.second;
		double center = f->NetXOut;
		double dist = netXOut - center;

		if (closestDist > std::abs(dist)) {
			closestDist = std::abs(dist);
			closestFact = f.get();
		}
	}

	FactRelevence fr(closestFact, closestDist);
	return fr;
}


void MetaBrain::CollapseFactKnowlegeSpaceMapping(){
    for(auto f : brainRef->facts){
        for(auto fo : brainRef->facts){
            if(f.second->senseData->hashId != fo.second->senseData->hashId){
                if(f.second->mapToType == fo.second->mapToType){
                    if(f.second->data() == fo.second->data()){
                        f.second->MutateCorrelation(fo.second->NetXOut);
                    }
                }
            }
        }
    }
}


