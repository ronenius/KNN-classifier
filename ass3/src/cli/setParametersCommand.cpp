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
        std::string input = this->getIO()->read();
        if (input.size() == 0)
        {
            return;
        }
        int index = input.find(' ');
        k = std::stoi(input);
        newMetric = input.substr(index + 1);
        if (k < 1 || k > 10)
            this->getIO()->write("Invalid value for K\n");
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
            this->getIO()->write("Invalid value for distance metric\n");
    }
    this->cli->setK(k);
    this->cli->setMetric(newMetric);
}