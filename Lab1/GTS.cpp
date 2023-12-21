#include "GTS.h"
#include "pipe.h"
#include "station.h"
#include "utils.h"
#include <sstream>
#include <stack>
#include <algorithm>
//#include <bits/stdc++.h>
#include <queue>

void GTS::addPipe()
{
    pipe pipe;
    std::cin >> pipe;
    ps.insert(std::make_pair(pipe.get_ID(), pipe));
}

void GTS::addKS()
{
    station station;
    std::cin >> station;
    ss.insert(std::make_pair(station.get_ID(), station));
}

void GTS::out_data()
{
    for (auto& [id, p] : ps)
        std::cout << p;
    for (auto& [id, s] : ss)
        std::cout << s;
}


bool ID_is_Present(std::unordered_set<int>& unordered_set, int value)
{
    int k = 0;
    for (auto kv : unordered_set)
    {
        if (kv == value)
            ++k;
    }
    if (k == 0)
        return false;
    else
        return true;
}

std::unordered_set<int> select_ids(std::unordered_set<int>& found_ids)
{
    // select ids in found pipes
    //
    std::stringstream ss;
    std::string str;

    std::unordered_set<int> selected_ids;
    std::unordered_set<int> notfound_ids;

    int id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, str);
    std::cerr << str;
    ss << str;
    while (!ss.eof())
    {
        char c = (char)ss.peek();
        if (isdigit(c))
        {
            ss >> id;
            if (ID_is_Present(found_ids, id))
                selected_ids.insert(id);
            else
                notfound_ids.insert(id);
        }
        else
        {
            ss.ignore();
        }

    }
    std::cout << "selected ids\n";
    for (auto el : selected_ids) std::cout << el << ' ';
    std::cout << "\n";
    std::cout << "not found ids\n";
    for (auto el : notfound_ids) std::cout << el << ' ';
    std::cout << "\n";

    return selected_ids;
}

void GTS::del_or_edit_ps(std::unordered_set <int>& found_ids)
{
    for (int id : found_ids)
    {
        std::cout << ps.at(id);
    }
    std::cout << "\nids\n";

    for (int id : found_ids)
        std::cout << id << ", ";

    std::cout << "\n";

    //choise select ids or exit

    std::cout << "select choise:\n"
        << "1. exit menu\n"
        << "2. edit pipes\n"
        << "3. del pipes\n"
        << "__> ";
    int choice2 = InputNum<int>(1, 3);

    std::unordered_set<int> selected_ids;

    if (choice2 == 1)
    {
        return;
    }
    else if (choice2 == 2)
    {

        std::cout << "select ids pipe to edit\n";
        selected_ids = select_ids(found_ids);
        std::cout << "\nInput mending(0/1) for pipes\n"
            << "__> ";
        bool rem = InputNum<bool>(false, true);

        for (int id : selected_ids)
            ps.at(id).set_remont(rem);
    }
    else
    {
        std::cout << "select ids pipe to delete\n";
        selected_ids = select_ids(found_ids);


        std::unordered_set<int> used(selected_ids.size() + id_used_edges.size());
        for (int i : selected_ids)
        {
            if (id_used_edges.count(i))
                used.insert(i);
        }

        //проверка на то что труба состоит в графе
        if (!used.empty())
        {
            std::cout << "Celected pipe(s) with id(s):  ";
            for (int i : used) std::cout << i << " ";
            std::cout << "  used in GTS !\n";
            std::cout << "Do you rly want to delete pipe(s)?\n(Y=1/n=0)\n" << "__>";
            int a = InputNum(0, 1);
            if (a) //удалить
            {
                for (int id : selected_ids)
                    ps.erase(id);

                // удалить связ
                for (int id : used)
                {
                    id_used_edges.erase(id_used_edges.find(id));
                    graph.erase(id);
                }

                std::cout << "\n";
                for (auto i : id_used_edges)
                    std::cout << i << " ";
                std::cout << "\n";
                for (auto i : id_used_vertexes)
                    std::cout << i << " ";

                // пересоздать граф
                GTS::Graph_and_Topsort();
            }
            else //не удалять
                return;
        }
        else //не используется в графе=удалить просто
        {
            for (int id : selected_ids)
                ps.erase(id);
        }
    }
}

void GTS::del_or_edit_ss(std::unordered_set <int>& found_ids)
{
    for (int id : found_ids)
        std::cout << ss.at(id);

    std::cout << "\nids\n";

    for (int id : found_ids)
        std::cout << id << ", ";

    std::cout << "\n";

    //choise select ids or exit

    std::cout << "select choise:\n"
        << "1. exit menu\n"
        << "2. edit stations\n"
        << "3. del stations\n"
        << "__> ";
    int choice2 = InputNum<int>(1, 3);

    //station& s = s;
    std::unordered_set<int> selected_ids;

    if (choice2 == 1)
    {
        return;
    }
    else if (choice2 == 2)
    {
        std::cout << "select ids station to edit\n";
        selected_ids = select_ids(found_ids);
        std::cout << "\nInput working cex for stations\n"
            << "__> ";
        int workcex = InputNum<int>(0, 100000);

        for (int id : selected_ids)
            ss.at(id).set_workingcex(workcex);
    }
    else
    {
        std::cout << "select ids station to delete\n";
        selected_ids = select_ids(found_ids);


        std::unordered_set<int> used(selected_ids.size() + id_used_vertexes.size());
        for (int i : selected_ids)
        {
            if (id_used_vertexes.count(i))
                used.insert(i);
        }

        //проверка на то что станция состоит в графе
        if (!used.empty())
        {
            std::cout << "Celected station(s) with id(s):  ";
            for (auto i : used) std::cout << i << " ";
            std::cout << "  used in GTS !\n";
            //std::cout<<"Previously you should delete pipes connected with that station(s)\n";
            std::cout << "Do you rly want to delete station(s)?\n(Y=1/n=0)\n" << "__>";
            int a = InputNum(0, 1);
            if (a) //удалить
            {
                for (auto id : selected_ids)
                    ss.erase(id);

                // удалить связ
                std::vector<int> arrKeys;
                for (int id : used)
                {
                    id_used_vertexes.erase(id_used_vertexes.find(id));

                    for (auto& element : graph)
                        if (element.second.id_in == id || element.second.id_out == id)
                        {
                            arrKeys.push_back(element.first);
                            //удалить трубы которые соединяются с этои? станцией из used_edges
                            id_used_edges.erase(id_used_edges.find(element.first));
                        }
                }

                for (auto i : arrKeys)
                    graph.erase(i);

                //убираем станции без труб из id_used_vertexes

//                std::vector<int> arrKeys2;
//                for (auto [id_pipe, path_] : graph)
//                    for (auto i:id_used_vertexes)
//                        if (i==path_.id_in || i==path_.id_out)
//                        {
//                            arrKeys2.push_back(i);
//                            std::cout<<i<<" ";
//                        }
//                for (auto i : id_used_vertexes)
//                    if (!(std::find(arrKeys2.begin(), arrKeys2.end(), i) == arrKeys2.end()))
//                            id_used_vertexes.erase(id_used_vertexes.find(i));

                std::cout << "\n";
                for (auto i : id_used_edges)
                    std::cout << i << " ";
                std::cout << "\n";
                for (auto i : id_used_vertexes)
                    std::cout << i << " ";

                // пересоздать граф
                GTS::Graph_and_Topsort();

            }
            else //не удалять
                return;
        }
        else //не используется в графе=удалить просто
        {
            for (int id : selected_ids)
                ss.erase(id);
        }
    }
}

//================================================== filters ===============================================

template <typename T>
using Filter = bool (*)(const pipe& p, T param);

bool CheckByName(const pipe& p, std::string param)
{
    if ((p.get_name_p()).find(param) == std::string::npos)
        return false;
    else
        return true;
}
bool CheckByRemont(const pipe& p, bool param)
{
    if (p.get_remont() == param)
        return true;
    else
        return false;
}

bool CheckByD(const pipe& p, int param)
{
    if (p.get_d() == param)
        return true;
    else
        return false;
}

template <typename T>
std::unordered_set<int> find(std::unordered_map<int, pipe>& ps, Filter<T> f, T param)
{
    std::unordered_set<int> found_ids;
    for (auto& [id, p] : ps)
    {
        if (f(p, param))
            found_ids.insert(id);
    }
    return found_ids;
}

void GTS::findPipes()
{
    std::cout << "select variable to find:\n"
        << "1. name pipe\n"
        << "2. remont pipe\n"
        << "__> ";
    int choice = InputNum<int>(1, 2);

    if (choice == 1)
    {
        std::cout << "Input name pipe\n"
            << "__> ";
        std::string name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, name);
        std::cerr << name;
        std::unordered_set<int> found_ids = find(ps, CheckByName, name);

        if (found_ids.empty())
            std::cout << "Not found \\_(._.)_/ \n";
        else
            del_or_edit_ps(found_ids);
    }
    else if (choice == 2)
    {
        std::cout << "Input remont pipe\n"
            << "__> ";
        bool rem = InputNum<bool>(false, true);
        std::unordered_set<int> found_ids = find(ps, CheckByRemont, rem);

        if (found_ids.empty())
            std::cout << "Not found \\_(._.)_/ \n";
        else
            del_or_edit_ps(found_ids);
    }
}



template <typename S>
using Filter2 = bool (*)(const station& s, S param);
bool CheckByName2(const station& s, std::string param)
{
    if ((s.get_name_s()).find(param) == std::string::npos)
        return false;
    else
        return true;
}
bool CheckByWCex(const station& s, int param)
{
    if (((int)(s.get_workingcex() / s.get_cex())) * 100 <= param)
    {
        return true;
    }
    else
        return false;
}

template <typename S>
std::unordered_set<int> find(std::unordered_map<int, station>& ss, Filter2<S> f, S param)
{
    std::unordered_set<int> found_ids;
    for (auto& [id, s] : ss)
    {
        if (f(s, param))
            found_ids.insert(id);
    }
    return found_ids;
}


void GTS::findKSs()
{
    std::cout << "select variable to find:\n"
        << "1. name KS\n"
        << "2. persent not working cex KS\n"
        << "__> ";
    int choice = InputNum<int>(1, 2);

    if (choice == 1)
    {
        std::cout << "Input name KS\n"
            << "__> ";
        std::string name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, name);
        std::cerr << name;
        std::unordered_set <int> found_ids = find(ss, CheckByName2, name);

        if (found_ids.empty())
            std::cout << "Not found \\_(._.)_/ \n";
        else
            del_or_edit_ss(found_ids);
    }
    else if (choice == 2)
    {
        std::cout << "Input persent not working cex KS\n"
            << "__> ";
        int persent = InputNum<int>(0, 100);
        std::unordered_set <int> found_ids = find(ss, CheckByWCex, persent);

        if (found_ids.empty())
            std::cout << "Not found \\_(._.)_/ \n";
        else
            del_or_edit_ss(found_ids);
    }
}

void GTS::link()
{
    path path = {};
    int id_pipe = 0;

    std::cout << "Input id first station\n" << "__> ";
    path.id_in = InputNum(1, station::get_newID());
    id_used_vertexes.insert(path.id_in);

    std::cout << "Input id second station\n" << "__> ";
    path.id_out = InputNum(1, station::get_newID());
    id_used_vertexes.insert(path.id_out);

    std::cout << "Input diameter pipe\n" << "__> ";
    int dia = InputNum(500, 1400);//500 700 1000 1400

    std::unordered_set<int> found_ids = find(ps, CheckByD, dia);

    if (found_ids.empty()) //Если трубы с таким диаметром нет
    {
        std::cout << "Pipe not found\nPlease create it\n";
        GTS::addPipe();

        //берём Id созданной трубы
        int id = (pipe::get_newID()) - 1;

        id_used_edges.insert(id);
        id_pipe = id;
        path.weight = ps.at(id_pipe).get_weight();

        //path.id_link = *(found_ids.begin());
    }
    else
    {
        std::cout << "found ids:  \n";
        for (auto el : found_ids) std::cout << el << ' ';
        std::cout << "\n";

        for (auto el : found_ids) //ищем трубу с таким диаметром
        {
            if (!ID_is_Present(id_used_edges, el)) //если труба не используется
            {
                id_used_edges.insert(el);
                id_pipe = el;
                path.weight = ps.at(id_pipe).get_weight();
                break;
            }
        }

        //Если найденная труба с данным диаметром есть, но используется
        if (id_pipe == 0)
        {
            std::cout << "All pipes with this diameter are used\nPlease create it\n";
            GTS::addPipe();

            //берём Id созданной трубы
            int id = (pipe::get_newID()) - 1;

            id_used_edges.insert(id);
            id_pipe = id;
            path.weight = ps.at(id_pipe).get_weight();
        }
    }

    graph.insert(std::make_pair(id_pipe, path));

    std::cout << "Your path is:\n" << "KS:(id:" << path.id_in << ")  ---Pipe:(id:" << id_pipe << ")--->  KS:(id:" << path.id_out << ")\n";

    Graph_and_Topsort();

}

std::ofstream& operator<<(std::ofstream& outf, const path& path)
{
    outf << path.id_in << "\n"
        << path.id_out << "\n"
        << path.weight << "\n";
    return outf;
}
std::ifstream& operator>>(std::ifstream& fin, path& path)
{
    fin >> path.id_in >> path.id_out >> path.weight;
    return fin;
}

void GTS::fileOut()
{
    std::string file;
    std::cout << "Input name file like 'something.txt'\n" << "__> ";
    std::cin >> file;
    std::ofstream outf(file);
    if (outf.is_open())
    {
        outf << pipe::get_newID() << "\n"
            << station::get_newID() << "\n";
        for (auto& [id, p] : ps)
        {
            // if (p.len > 0)
            outf << p;
        }
        for (auto& [id, s] : ss)
        {
            // if (station::s.cex > 0)
            outf << s;
        }
        for (auto& [id, path] : graph)
        {
            outf << "-\n";
            outf << id << "\n";
            outf << path;
        }
        for (auto el : id_used_edges)
            outf << "e\n" << el << "\n";

        for (auto el : id_used_vertexes)
            outf << "v\n" << el << "\n";
    }
    outf.close();
}

void GTS::fileIn()
{
    std::string file;
    std::cout << "Input name file like 'something.txt'\n" << "__> ";
    std::cin >> file;
    std::ifstream fin(file);
    std::string flag;
    if (fin.is_open())
    {
        pipe p;
        station s;
        path path{};
        int id_edge, id_vertex, a, b;
        int id;

        fin >> a >> b;
        p.set_newID(a);
        s.set_newID(b);
        while (getline(fin, flag))
        {
            if (flag == "p")
            {
                fin >> p;
                ps.insert(std::make_pair(p.get_ID(), p));
            }
            if (flag == "s")
            {
                fin >> s;
                ss.insert(std::make_pair(s.get_ID(), s));
            }
            if (flag == "-")
            {
                fin >> id;
                fin >> path;
                graph.insert(std::make_pair(id, path));
            }
            if (flag == "e")
            {
                fin >> id_edge;
                id_used_edges.insert(id_edge);
            }
            if (flag == "v")
            {
                fin >> id_vertex;
                id_used_vertexes.insert(id_vertex);
            }
        }
    }
    fin.close();
}

void printGraph(std::unordered_map<int, path>& graph)
{
    std::cout << "\nYour graph:\n";
    for (auto [id_pipe, path_] : graph)
        std::cout << "(id:" << path_.id_in << ") ---(id:" << id_pipe << ")---> (id:" << path_.id_out << ")\n";

}

bool Has_cycle(int vertex_count, int edge_count, std::vector<std::vector <int>> graph_no_weight, int v, std::vector<int>& visited)
{
    visited[v] = 1;
    for (int to : graph_no_weight[v])
        if (visited[to] == 0 && Has_cycle(vertex_count, edge_count, graph_no_weight, to, visited) || visited[to] == 1)
            return true;
    visited[v] = 2;
    return false;
}

void dfs(std::vector<std::vector <int>>& graph, int v, std::vector<int>& visited, std::vector <int>& order)
{
    visited[v] = 1;
    for (int to : graph[v])
        if (!visited[to])
            dfs(graph, to, visited, order);
    //    for(int u=0; u<graph.size(); u++)
    //        if(graph[v][u]==1 && !visited[u])
    //            dfs(graph, u, visited, order);
    order.push_back(v);
}

void topologicalSort(int vertex_count, std::vector<std::vector <int>> graph_no_weight)
{
    std::vector<int> visited(vertex_count, 0);
    std::vector<int> order;
    for (int i = 0; i < vertex_count; i++)
        if (!visited[i])
            dfs(graph_no_weight, i, visited, order);

    reverse(order.begin(), order.end());

    for (int i : order)
        std::cout << i + 1 << " ";

}

std::vector<std::vector <int>> GTS::make_graph_no_weight()
{
    int vertex_count = (int)id_used_vertexes.size();
    std::vector<std::vector <int>> graph_no_weight(vertex_count);
    for (int i : id_used_vertexes)
        for (auto [id_pipe, path_] : graph)
            graph_no_weight[path_.id_in - 1].push_back(path_.id_out - 1);

    return graph_no_weight;
}

void GTS::Graph_and_Topsort()
{

    int edge_count = (int)id_used_edges.size();
    int vertex_count = (int)id_used_vertexes.size();

    printGraph(graph);

    std::vector<std::vector <int>> graph_no_weight = make_graph_no_weight();

    // Топологическая сортировка

    std::vector<int> visited(vertex_count);
    for (int v = 0; vertex_count > v; v++)
    {
        if (Has_cycle(vertex_count, edge_count, graph_no_weight, v, visited))
        {
            std::cout << "Graph has cycle!!!\n";
            break;
        }
        else
        {
            std::cout << "Topsort:\n";
            topologicalSort(vertex_count, graph_no_weight);
            break;
        }
    }
}

void GTS::MaxFlow() // ( Edmonds-Karp algorithm )
{
    int edge_count = (int)id_used_edges.size();
    int vertex_count = (int)id_used_vertexes.size();
    std::vector<std::vector <int>> graph_no_weight = make_graph_no_weight();
    std::vector<int> visited(vertex_count);


    if (Has_cycle(vertex_count, edge_count, graph_no_weight, 0, visited))
    {
        std::cout << "Graph has cycle!!!\n";
        return;
    }
    else
    {
        int n;

        n = vertex_count;
        //m = edge_count;
        std::vector<std::vector<int>> c(vertex_count, std::vector<int>(n)), f(n, std::vector<int>(n)), g(n);
        int from, to, cost;


        for (auto [id_pipe, path_] : graph) {
            from = path_.id_in;
            to = path_.id_out;
            cost = (int)ps.at(id_pipe).get_efficiency();

            to--, from--;
            g[from].push_back(to);
            c[from][to] = cost;
        }


        // s - исток, t - сток

        std::cout << "Input source and target\n";
        int s = InputNum<int>(0, n) - 1;
        int t = InputNum<int>(0, n) - 1;

        bool found;
        while (true) {
            std::vector<int> pth(n, -1);
            std::queue<int> q;
            // помещаем s в очередь
            q.push(s);
            pth[s] = s;
            found = false;
            while (!q.empty() && !found) {
                from = q.front();
                q.pop();
                for (size_t j = 0; j < g[from].size() && !found; j++) {
                    to = g[from][j];
                    if (pth[to] == -1 && c[from][to] - f[from][to] > 0) {
                        q.push(to);
                        pth[to] = from;
                        found = to == t;
                    }
                }
            }
            // если увеличивающий путь из s в t не найден
            if (!found) {
                break;
            }
            // ищем минимальную величину, на которую можно увеличить поток
            int cf = INF;
            for (to = n - 1; to != s;) {
                from = pth[to];
                cf = std::min(cf, c[from][to] - f[from][to]);
                to = from;
            }
            // увеличиваем поток на эту величину, уменьшая при этом поток для обратныъ ребер
            for (to = n - 1; to != s;) {
                from = pth[to];
                f[from][to] += cf;
                f[to][from] -= cf;
                to = from;
            }
        }
        int flow = 0;
        for (size_t j = 0; j < g[s].size(); ++j) {
            flow += f[s][g[s][j]];
        }
        std::cout << "Max flow  from " << s + 1 << " to " << t + 1 << " = " << flow << std::endl;

    }
}

typedef std::pair<int, int> pair; //первое число пары — куда оно ведёт, второе — длина ребра

std::vector<int> dijkstra(int s, int t, int n, std::vector < std::vector < pair > >& adj) {

    std::vector<int> d(n, INF), p(n);
    d[s] = 0;
    int ves;
    std::vector<char> u(n);
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == INF)
            break;
        u[v] = true;

        for (size_t j = 0; j < adj[v].size(); ++j) {
            int to = adj[v][j].first,
                len = adj[v][j].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
            ves = d[v + 1];/////
        }
    }

    std::vector<int> path;
    int k = 0;
    for (int v = t; v != s; v = p[v]) {
        path.push_back(v);
        k++;
        if (k > 10000)
            return {};
    }
    path.push_back(s);
    reverse(path.begin(), path.end());

    std::cout << "path weigth:  " << ves << '\n';
    return path;
}

void GTS::min_path() {

    int vertex_count = (int)id_used_vertexes.size();



    std::vector < std::vector < pair > > gr(vertex_count);
    for (auto [id_pipe, path_] : graph) {
        int cost = (int)ps.at(id_pipe).get_weight();
        gr[path_.id_in - 1].emplace_back(path_.id_out - 1, cost);
    }


    std::cout << "Input source and target\n";
    int s = InputNum<int>(0, vertex_count) - 1;
    int t = InputNum<int>(0, vertex_count) - 1;

    std::vector min_pth = dijkstra(s, t, vertex_count, gr);
    if (min_pth.empty())
        std::cout << "No way\n";
    else
    {
        std::cout << "Min path from " << s + 1 << " to " << t + 1 << " = ";
        for (auto i : min_pth)
            std::cout << i + 1 << " ";
        std::cout << std::endl;
    }
}