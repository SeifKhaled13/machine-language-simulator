// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include <bits/stdc++.h>
#include "Machine.cpp"
#define all(v) v.begin(), v.end()
#define each auto &
using namespace std;

int main()
{
    Machine machine;
    int op;
    vector<string> ls{
        "Load new program",
        "Show screen content",
        "Show register content",
        "Show memory content",
        "Run until halt",
        "Run one cycle",
    };
    cout << "Welcome <3 \n";
    while (true)
    {
        int list_size = (machine.halted() ? 4 : 6);
        cout << "====================================\n";
        for (vector<string>::iterator i = ls.begin(); i != ls.end(); ++i)
        {
            cout << distance(ls.begin(), i) + 1 << "-" << *i << endl;
        }
        cout << "0-Exit\n";
        cout << "====================================\n";
        cout << "Insert Here --> " << endl;
        cin >> op;
        if (op < 0 || op > list_size)
            continue;

        if (op == 0)
        {
            exit(0);
        }
        else if (op == 1)
        {
            machine.reset();
            string file_name, ins, content;
            char c;
            int idx{};
            cout << "Filename: ";
            cin >> file_name;
            ifstream fs(file_name);
            while (true)
            {
                string hex_idx;
                cout << "Starting at (hex index): ";
                cin >> hex_idx;
                idx = base_to_dec(hex_idx, 16);
                if (idx >= 0 && idx < 256)
                    break;
            }
            while (fs >> c)
            {
                content.push_back(c);
            }
            for (int i = 0; i + 1 < content.size(); i += 2)
            {
                ins.push_back(content[i]), ins.push_back(content[i + 1]);
                machine.atM(idx).set_value(base_to_dec(ins, 16));
                idx++;
                ins.clear();
            }
        }
        else if (op == 2)
        {
            cout << machine.sceen_content() << endl;
        }
        else if (op == 3)
        {
            for (int i = 0; i < machine.registerCount(); i++)
            {
                cout << 'R' << dec_to_base(i, 16) << ": " << machine.atR(i).hex_value() << endl;
            }
            cout << "PC: " << machine.PC() << " IR: " << machine.IR() << endl;
        }
        else if (op == 4)
        {
            cout << "  ";
            for (int i = 0; i < 16; i++)
            {
                char c = (i < 10 ? i + '0' : i - 10 + 'A');
                cout << c << "  ";
            }
            cout << endl;
            for (int i = 0; i < 16; i++)
            {
                char c = (i < 10 ? i + '0' : i - 10 + 'A');
                cout << c << " ";
                for (int j = 0; j < 16; j++)
                {
                    cout << machine.atM(i * 16 + j).hex_value() << " ";
                }
                cout << endl;
            }
        }
        else if (op == 5)
        {
            while (!machine.halted())
            {
                machine.run_one_cycle();
            }
        }
        else if (op == 6)
        {
            machine.run_one_cycle();
        }
    }

    return 0;
}

