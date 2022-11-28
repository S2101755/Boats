//
//* Author S.M
//*

#include "TrainAndTest.h"
#include "StructureDefinitions.h"


//variables for storing to training data and its characteristics
static    double myModel[NUM_TRAINING_SAMPLES][ NUM_FEATURES]; ///< local copy of the training data
static int myModelLabels[NUM_TRAINING_SAMPLES]; ///< local copy of the labels in the trainig data

static int numClasses = 0; ///< store the number of differtent class labels in the treainig set
static int validLabels[256]; ///< keep a list of what those valid labels are
static int trainingSetSize=0; ///< keep traick of how many examples (rows) are in the trainig set
static int trainingSetFeatures = 0; ///< record how mangy features (columns) were in the training set
static double minVal[NUM_FEATURES];
static double maxVal[NUM_FEATURES];
static bool modelTrained = false; ///< keep track of whether we have trained our model or not


//Variables workingCandidate, openList, closedList for use in freedy local search for best set of rules
candidateSolution workingCandidate;// this one will hold the solutions we are currently considering
candidateList  openList; // this list will store all the solutions we've created but not examined yet
candidateList closedList; // this is where we will store all the ones we're done with




int  train( double **trainingSamples, int *trainingLabels, int numSamples, int numFeatures)
{

    StoreData(trainingSamples, trainingLabels, numSamples, numFeatures);

    
    printf("\nAbout to Learn rules:\n");
    
    GreedyConstructiveSearch();
    
  
    printWorkingCandidate();


    modelTrained = true;
    
    return (1);
}


int   predictLabel(double *sample, int numFeatures)
{
    
    if(validLabels[0]==NO_PREDICTION)
        PrintThisMessageAndExit("predictLabel called before StoreData() so can't know what the valid labels are");
    
    
    int rulesInCandidate = workingCandidate.size/VALUES_PER_RULE;
    
 
    int thePrediction= NO_PREDICTION;
    rule thisRule;
    
   int i;
    for (i = 0; i < rulesInCandidate && thePrediction == NO_PREDICTION; i++)
    {
        thisRule.variableAffected = workingCandidate.variableValues[VALUES_PER_RULE * i];
        thisRule.comparison = workingCandidate.variableValues[VALUES_PER_RULE * i + 1];
        thisRule.threshold = workingCandidate.variableValues[VALUES_PER_RULE * i + 2];
        thisRule.prediction = workingCandidate.variableValues[VALUES_PER_RULE * i + 3];

        thePrediction = PredictClassFromRule(thisRule, sample, numFeatures);
    }

    

    if (modelTrained == true && thePrediction == NO_PREDICTION) {
        thePrediction = validLabels[1];
    }
 
    
    return thePrediction;
    
}




void GreedyConstructiveSearch(void)
{
    int bestSoln;
    bool atGoal=false;
    rule newrule;
    int variable, operator,threshold,prediction;
    
    
    candidateSolution tmp;
    
    

    CleanListsOfSolutionsToStart();
    CleanWorkingCandidate();
    workingCandidate.score = 0;
    atGoal = false;
    CleanCandidate(&tmp);
    tmp.score = -1;
    
    
    AddWorkingCandidateToOpenList();
    
 
    while (atGoal == false) {

        // Set tmp as workingCandidate
        tmp = workingCandidate;

        // Generate evey possible rule and for each rule
        for (variable = 0; variable < trainingSetFeatures; variable++)
        {
            for (operator = 0; operator < NUM_OPERATORS; operator++)
            {
                for (threshold = 0; threshold < THRESHOLD_PRECISION; threshold++)
                {
                    for (prediction = 0; prediction < numClasses; prediction++)
                    {
                        workingCandidate = tmp;

                        
                        newrule.variableAffected = variable;
                        newrule.comparison = operator;
                        newrule.threshold = threshold;
                        newrule.prediction = prediction;

                        
                        ExtendWorkingCandidateByAddingRule(newrule);

                        
                        ScoreWorkingCandidateOnTrainingSet();

                        
                        if (workingCandidate.score != NO_PREDICTION) {
                            AddWorkingCandidateToOpenList();
                        }
                    }
                }
            }
        }

        // Adding tmp to closed list
        AddCandidateParam1_ToListParam2(&tmp, &closedList);

        
        int i,j;
        for (i = 0; i <= openList.size - 1; i++)
        {
            for (j = 0; j <= openList.size - i - 1; j++) {
                if (openList.listEntries[j].score < openList.listEntries[j + 1].score) {
                    candidateSolution temp = openList.listEntries[j];
                    openList.listEntries[j] = openList.listEntries[j + 1];
                    openList.listEntries[j + 1] = temp;
                }
            }
        }

        // Setting the first element of the openList to be the workingCandidate
        CopySolutionFromOpenListIntoWorkingCandidate(0);

        // Emptying the open list
        int currentSolution;
        for (currentSolution = 0; currentSolution <= openList.size; currentSolution++)
        {
            CleanCandidate(&openList.listEntries[currentSolution]);
        }
        openList.size = 0;

        // Checking if goal found
        atGoal = GoalFound();
    }
    
   
    
    if(!atGoal)
        printf("Left Search without classifying all examples\n");
 
    
 
    if(workingCandidate.score >= tmp.score   )
        CopySolution(&workingCandidate, &tmp);
    else
        CopySolution(&tmp, &workingCandidate);
}





       
void ScoreWorkingCandidateOnTrainingSet(void)
{
    int numWrong=0, numRight=0;

    int thePrediction = NO_PREDICTION;
    //safety checking
    if(trainingSetSize<=0)
        PrintThisMessageAndExit("called ScoreWorkingCandidateOnTrainingSet() before training set has been loaded\n");
    
    //loop through the training set
    int nextSample;
    for( nextSample=0; nextSample < trainingSetSize; nextSample++)
    {
        //make prediction
        thePrediction =  predictLabel(myModel[nextSample], trainingSetFeatures);
        //increment score if correct
        if (thePrediction== myModelLabels[nextSample])
            numRight++;
        else if (thePrediction != NO_PREDICTION)
            numWrong++;
 
    }
 

    if(numWrong>0)
        workingCandidate.score= -1; 
    else
        workingCandidate.score = numRight;
    
    
}
 


int PredictClassFromRule(rule thisRule, double * sample, int numFeatures )
{
 
    int prediction = NO_PREDICTION;
    double percent, range, theThreshold;
    int feature = thisRule.variableAffected;
    //check the sample contains a value for the variable the rule covers
    if( feature< 0 || feature >= numFeatures  )
        printf("rule uses variable not present in sample");
    else
    {
        percent = (double) thisRule.threshold/100.0;
        range = maxVal[feature] - minVal[feature];
        theThreshold = minVal[feature] + percent*range;
    //apply the operator
        switch(thisRule.comparison)
        {
            case lessThan:
                if ( sample[feature] < theThreshold)
                    prediction = thisRule.prediction;
                break;
            case equals:
                if ( sample[feature] == theThreshold)
                    prediction = thisRule.prediction;
                break;
            case greaterThan:
                if ( sample[feature] > theThreshold)
                    prediction = thisRule.prediction;
                break;
            default: PrintThisMessageAndExit("rule contains unknown comparator");
        }
    }
    
    return prediction;
    
}





bool GoalFound(void)
{
    if(workingCandidate.score < trainingSetSize && workingCandidate.size < VALUES_PER_RULE*MAX_NUM_RULES)
        return( false);
    else
        return true;
}

void printWorkingCandidate (void)
{
    int index, rule, numrules;
    

    if (workingCandidate.size == 0)
        PrintThisMessageAndExit("workingCandidate does not seem to hold any rules\n ");
 
  else
  {
      numrules = workingCandidate.size/VALUES_PER_RULE;
      printf("Learned model  has %d rules and scores %d:\n",  numrules, workingCandidate.score);
      for( rule=0;rule<numrules; rule++)
        {
            index = rule*4;
            int feature = workingCandidate.variableValues[index];
            int operator = (workingCandidate.variableValues[index+1]);
            char op = (operator == lessThan)? '<': (operator== equals)? '=':'>';
            int thresh = (workingCandidate.variableValues[index+2]);
            double percent = (double) thresh/100.0;
            double range = maxVal[feature] - minVal[feature];
            double theThreshold = minVal[feature] + percent*range;
            int prediction = workingCandidate.variableValues[index+3];
            
            printf("\t%s feature %d %c %lf  CLASS = %d\n",(rule==0)?"IF": "ELSE IF",feature,op, theThreshold, prediction);
 
          }
  }
}








void ExtendWorkingCandidateByAddingRule(rule newRule)
{
 extern candidateSolution workingCandidate;
    //check it isn't already full
    if (workingCandidate.size==N)
        {
            PrintThisMessageAndExit (" can't add rule to already full working candidate");
        }
    else
     {
         ExtendWorkingCandidateByAddingValue(newRule.variableAffected);
         ExtendWorkingCandidateByAddingValue(newRule.comparison);
         ExtendWorkingCandidateByAddingValue(newRule.threshold);
         ExtendWorkingCandidateByAddingValue(newRule.prediction);

     }
}




void prepareTrainingDataArrays(int numSamples, int numFeatures)
{
    int feature, sample, label;
    //clean the arrays because C leaves whatever is in the memory
     for ( sample=0; sample < NUM_TRAINING_SAMPLES; sample++)
     {
         myModelLabels[sample]= UNUSED;
         for ( feature=0; feature<NUM_FEATURES; feature++)
             myModel[sample][feature] = 0.0;
     }
     for ( label=0; label<256; label++)
         validLabels[label] = NO_PREDICTION;
    
     
     for(feature=0;feature < NUM_FEATURES;feature++)
       {
       minVal[feature] = BIG_DBL; //no point guessing what the smallest possible value is
       maxVal[feature] = 0.0;
     }
     
     //sanity checking
     if ( numFeatures > NUM_FEATURES || numSamples > NUM_TRAINING_SAMPLES)
         PrintThisMessageAndExit ("error: called train with data set larger than spaced allocated to store it");
         
}



void StoreData(double **trainingSamples, int *trainingLabels, int numSamples, int numFeatures)
{

int label,sample, feature;
int thisLabel;
double thisVal;
int labelUsed[256];
    
    modelTrained = false;
    for(label=0;label<256;label++)
        labelUsed[label] = 0;
    prepareTrainingDataArrays(numSamples, numFeatures);
    
    //store the data
    trainingSetFeatures = numFeatures;
    trainingSetSize = numSamples;
    for (sample=0; sample < numSamples; sample++)
        {
            myModelLabels[sample] = trainingLabels[sample];
            for (feature=0; feature < numFeatures; feature++)
              {
                  thisVal = trainingSamples[sample][feature];
                  myModel[sample][feature] = thisVal;
                  if (thisVal < minVal[feature])
                      minVal[feature] = thisVal;
                  if (thisVal > maxVal[feature])
                      maxVal[feature] = thisVal;
              }
              //record which labels have been used
              thisLabel = trainingLabels[sample];
              labelUsed[thisLabel] ++ ;
          }
    // work out how many, and which,  labels were present in the trainig set
    numClasses = 0;
    for(label=0;label < 256;label++)
        {
        if( labelUsed[label]>0)
           {
            validLabels[numClasses] = label;
            numClasses++;
            }
        }
           
    fprintf(stdout,"data stored locally with %d examples and %d features\n",trainingSetSize,trainingSetFeatures);
    for(feature=0;feature<trainingSetFeatures;feature++)
        printf("\tfeature %d has minVal %f and maxVal %f \n", feature, minVal[feature],maxVal[feature]);
}



int main(int argc,char**argv){
    extern int Xmain(void);
    return Xmain( );
    
}


