#!/usr/bin/env sh

files=$(ls $1 | grep -Eio "^Day[0-9]+\.hpp$")
if [[ -z $files ]]; then
cat > $2 << EOM
#pragma once
#include <memory>
#include <IDay.hpp>

std::array<std::shared_ptr<IDay>, 0> days = {};
EOM

    exit
fi

cat > $2 << EOM
#pragma once
#include <memory>
#include <IDay.hpp>

$(echo "$files" | sed -nE 's/^(Day[0-9]+\.hpp)$/#include <Days\/\1>/p')

std::array<std::shared_ptr<IDay>, $(echo "$files" | wc -l)> days = {
$(echo "$files" | sed -En "s/^Day0*([0-9]+).hpp$/    std::make_shared<Day\1>(),/p")
};
EOM