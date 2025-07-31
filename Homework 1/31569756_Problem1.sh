#!/bin/bash

printf " ____________________________________________________________________\n"
sleep 1
printf "|              Welcome to the Rock Paper Scissors Game!              |\n"
sleep 1
printf "|                     The game is fairly simple.                     |\n"
sleep 1
printf "| You have to enter a value for rock, paper, or scissors             |\n"
sleep 1
printf "|    Be sure to strictly enter the values above to play.             |\n"
sleep 1
printf "|    Rock beats scissors, scissors beats paper, paper beats rock.    |\n"
sleep 1
printf "|  If there is a tie, keep playing until a winner has been decided.  |\n"
sleep 1
printf "|____________________________________________________________________|\n\n"
sleep 1
printf "Choose one of the following, rock, paper, or scissors: "

read rps

printf "You chose $rps!\n"

comChoice=$((RANDOM%3))

if [ $comChoice -eq 0 ]; then
  comChoice="rock"
elif [ $comChoice -eq 1 ]; then
  comChoice="paper"
else
  comChoice="scissors"
fi


printf "The computer chose: $comChoice \n\n"

if [ "$rps" == "$comChoice" ]; then
  while [ "$rps" == "$comChoice" ]; do
    printf "You have tied with the computer, please try again! \n\n"
    printf "Choose one of the following, rock, paper, or scissors: "
    read rps
    printf "You chose $rps!\n\n"
    comChoice=$((RANDOM%3))
    if [ $comChoice -eq 0 ]; then
      comChoice="rock"
    elif [ $comChoice -eq 1 ]; then
      comChoice="paper"
    else
      comChoice="scissors"
    fi
    printf "The computer's new choice is: $comChoice \n"
  done


  if [ "$rps" = "rock" ] && [ "$comChoice" = "scissors" ]; then
    printf "You win, rock beats scissors! \n\n"
  elif [ "$rps" = "paper" ] && [ "$comChoice" = "rock" ]; then
    printf "You win, paper beats rock! \n\n"
  elif [ "$rps" = "scissors" ] && [ "$comChoice" = "paper" ]; then
    printf "You win, scissors beats paper!\n\n"
  else
    printf "The computer won, you lost :( \nPlay again!\n\n"
  fi


elif [ "$rps" = "rock" ] && [ "$comChoice" = "scissors" ]; then
  printf "You win, rock beats scissors! \n\n"
elif [ "$rps" = "paper" ] && [ "$comChoice" = "rock" ]; then
  printf "You win, paper beats rock! \n\n"
elif [ "$rps" = "scissors" ] && [ "$comChoice" = "paper" ]; then
  printf "You win, scissors beats paper!\n\n"
else
  printf "The computer won, you lost :(\n Play again!"
fi
