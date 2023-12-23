#ifndef __DAY19_HPP__
#define __DAY19_HPP__

#include <day.hpp>
#include <stdio.h>

class Day19 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;

    enum RuleComparator {
        LESS = '<',
        GREATER = '>'
    };

    enum Redirects {
        ACCEPT = 'A',
        REJECT = 'R'
    };

    struct Rule {
        char part;
        char comparator;
        size_t value;
        
        std::string redirect;
    };

    struct Workflow {
        std::string label;
        std::vector<Rule> rules;
        std::string defaultRedirect;
    };

    enum PartRatings {
        X = 'x',
        M = 'm',
        A = 'a',
        S = 's'
    };
    
    struct Part {
        char part;
        size_t value;
    };

    struct Ratings {
        Part parts[4];    
    };

    std::vector<Workflow> workflows;
    robin_hood::unordered_flat_map<std::string, size_t> workflowIndexes;

    std::vector<Ratings> ratings;
    
public:
    Workflow readWorkflow(const std::string& str) {
        size_t readChars = 0;

        Workflow workflow;
        Rule rule;

        const char* cur = str.c_str();
        const char label[4] = { 0, 0, 0, 0 };

        sscanf(cur, "%[^{]{%n", label, &readChars);
        workflow.label = std::string(label);

        cur += readChars;
        while(sscanf(cur, "%c%c%zu:%[^,],%n", &rule.part, &rule.comparator, &rule.value, &label, &readChars) == 4) {
            rule.redirect = std::string(label);

            workflow.rules.push_back(rule);

            rule = {};
            cur += readChars;
        }

        sscanf(cur, "%[^}]", &label);
        workflow.defaultRedirect = std::string(label);

        return workflow;
    }

    Ratings readRatings(const std::string& str) {
        const char* cur = str.c_str() + 1;
        size_t readChars = 0;

        Ratings rating;
        sscanf(cur, "%c=%zu,%c=%zu,%c=%zu,%c=%zu",
            &rating.parts[0].part, &rating.parts[0].value,
            &rating.parts[1].part, &rating.parts[1].value,
            &rating.parts[2].part, &rating.parts[2].value,
            &rating.parts[3].part, &rating.parts[3].value);

        return rating;
    }


    void loadInput() {
        bool readingWorkflows = true;

        for(std::string& str : input) {
            if(str.size() <= 0) {
                readingWorkflows = false;
                continue;
            }

            if(!readingWorkflows) ratings.push_back(readRatings(str));
            else {
                const Workflow& workflow = readWorkflow(str);

                workflows.push_back(workflow);
                workflowIndexes[workflow.label] = workflows.size() - 1;
            }
        }
    }

    void partA() {
        if(workflows.size() <= 0) loadInput();
        partASolution = 0;
        
        for(Ratings rating : ratings) {
            bool done = false;
            bool accepted = false;

            std::string redirect = "in";

            while(!done) {
                switch(redirect[0]) {
                case Redirects::ACCEPT: done = true; accepted = true; break;
                case Redirects::REJECT: done = true; accepted = false; break;
                default: break;
                }

                if(done) break;
                
                Workflow* workflow = &workflows[workflowIndexes[redirect]];

                bool foundRule = false;
                for(const Rule& rule : workflow->rules) {
                    Part* part;

                    switch(rule.part) {
                    case PartRatings::X: part = &rating.parts[0]; break;
                    case PartRatings::M: part = &rating.parts[1]; break;
                    case PartRatings::A: part = &rating.parts[2]; break;
                    case PartRatings::S: part = &rating.parts[3]; break;
                    default: break;
                    }

                    bool valid = (rule.comparator == RuleComparator::GREATER ? part->value > rule.value : part->value < rule.value);
                    if(!valid) continue;

                    redirect = rule.redirect;
                    foundRule = true;

                    break;
                }

                if(foundRule) continue;
                redirect = workflow->defaultRedirect;
            }

            if(!accepted) continue;

            for(Part part : rating.parts) {    
                partASolution += part.value;
            }
        }
    }

    void partB() {
        partBSolution = 0;
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day19() : Day("input/day19.txt") {}
};

#endif