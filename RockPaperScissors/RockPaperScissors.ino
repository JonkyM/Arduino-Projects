int userInput; // String for the user's input
int randNum; //Variable used to store the randomly generated number

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(millis());
}

void loop() 
{
  // The computers choice depends on the following random nums:
  // 0 = rock, 1 = paper, 2 = scissors

  randNum = random(3);
  Serial.println("Enter Your Move (1 = rock, 2 = paper, or 3 = scissors):");
  while(!Serial.available()){};
  userInput = Serial.parseInt();

  if(userInput == 1) //Evaluates the possible outcomes if user chooses rock
  {
    Serial.println("You Chose Rock!!");
    if(randNum == 0)
    {
      Serial.println("The Computer Chose Rock!!");
      Serial.println("ITS A TIE");
    }
    else if(randNum == 1)
    {
      Serial.println("The Computer Chose Paper!!");
      Serial.println("YOU LOSE!!");
    }
    else if(randNum == 2)
    {
      Serial.println("The Computer Chose Scissors!!");
      Serial.println("YOU WIN!!");
    }
    else
    {
      Serial.println("Uh Oh... Something went wrong.");
    }
  }
  else if(userInput == 2) //Evaluates the possible outsomes if the user chooses paper
  {
    Serial.println("You Chose Paper!!");
    if(randNum == 0)
    {
      Serial.println("The Computer Chose Rock!!");
      Serial.println("YOU WIN!!");
    }
    else if(randNum == 1)
    {
      Serial.println("The Computer Chose Paper!!");
      Serial.println("ITS A TIE");
    }
    else if(randNum == 2)
    {
      Serial.println("The Computer Chose Scissors!!");
      Serial.println("YOU LOSE!!");
    }
    else
    {
      Serial.println("Uh Oh... Something went wrong.");
    }
  }
  else if(userInput == 3) //Evaluates the possible outcomes if the user chooses scissors
  {
    Serial.println("You Chose Scissors!!");
    if(randNum == 0)
    {
      Serial.println("The Computer Chose Rock!!");
      Serial.println("YOU LOSE!!");
    }
    else if(randNum == 1)
    {
      Serial.println("The Computer Chose Paper!!");
      Serial.println("YOU WIN!!");
    }
    else if(randNum == 2)
    {
      Serial.println("The Computer Chose Scissors!!");
      Serial.println("ITS A TIE");
    }
    else
    {
      Serial.println("Uh Oh... Something went wrong.");
    }
  }
  else //This happens if the user doesnt input a valid choice, or if we really messed up
  {
    Serial.println("Erm... either something went wrong or you misspelled your input. Try again.");
  }
}
