#include "setParametersCommand.hpp"

setParametersCommand::setParametersCommand(defaultIO *dio, CLI *cli)
    : command(dio, "algorithm settings"), cli(cli){};

void setParametersCommand::execute()
{
    this->getIO()->write("The current KNN parameters are: K = " + std::to_string(this->cli->getK()) +
                         ", distance metric = " + this->cli->getMetric() + "\n");
    bool isKCorrect = false, isMetricCorrect = false;
    int k;
    std::string newMetric;
    while (!isKCorrect || !isMetricCorrect)
    {
        isKCorrect = false;
        isMetricCorrect = false;
        std::string input = this->getIO()->read(), errorMessage = "";
        if (input == "\n")
        {
            return;
        }
        int index = input.find(' ');
        bool flag = true;
        if (index < 0)
            flag = false;
        for (int i = 0; i < index; i++)
        {
            if (!isdigit(input[i]))
                flag = false;
        }
        if (flag)
            k = std::stoi(input);
        newMetric = input.substr(index + 1);
        if (!flag || k < 1 || k > 10)
            errorMessage = "Invalid value for K\n";
        else
            isKCorrect = true;
        for (int i = 0; i < this->cli->getPossibleMetrics().size(); i++)
        {
            if (newMetric.compare(this->cli->getPossibleMetrics()[i]) == 0)
            {
                isMetricCorrect = true;
            }
        }
        if (!isMetricCorrect)
            errorMessage += "Invalid value for distance metric\n";
        if (!isKCorrect || !isMetricCorrect)
            this->getIO()->write(errorMessage);
    }
    this->cli->setK(k);
    this->cli->setMetric(newMetric);
}