#pragma once
#include<vector>
#include <windows.h>
#include<time.h>
#include<unordered_map>
#include<sql.h>
#include"../aqpp/sql_interface.h"
#include"../aqpp/common_content.h"
#include"../exp/exp_common.h"
#include"../aqpp/precompute.h"
//#include"../aqpp/dist_mtl_points.h"
#include"../aqpp/assign_budget_for_dimensions.h";
#include"../aqpp/hill_climbing.h"
#include"../aqpp/aqpp.h"
#include"../aqpp/tool.h"
#include"../aqpp/stratified_sampling.h"
#include"../aqpp/stratified_aqpp.h"
#include <string>
#include<iostream>
using namespace aqppp;
//using namespace Algo;
using namespace std;
namespace Exp {
	class Exp_groupby {
	private:
		static string dirpath(void);

		static const Settings init_par();
		
		typedef unordered_map<vector<string>, double,VectorHash> GpType4Str;
		typedef unordered_map<vector<int>, double, VectorHash> GpType4Int;

		struct EXP_PAR
		{
			bool isMTL;
			bool EXP_NO_UNIFORM;
			bool QUERY_DB_REAL_VALUE;
			bool COVER_DIRECT_RESULT_FILE;  //generally this should be false.
			int QUERY_NUM;
			double MIN_QUERY_SELECTIVELY;
			double MAX_QUERY_SELECTIVELY;

			EXP_PAR() = default;

			EXP_PAR(bool isMTL, bool EXP_NO_UNIFORM, bool QUERY_DB_REAL_VALUE, bool COVER_DIRECT_RESULT_FILE, int QUERY_NUM, double MIN_QUERY_SELECTIVELY, double MAX_QUERY_SELECTIVELY)
				: isMTL(isMTL), EXP_NO_UNIFORM(EXP_NO_UNIFORM), QUERY_DB_REAL_VALUE(QUERY_DB_REAL_VALUE), COVER_DIRECT_RESULT_FILE(COVER_DIRECT_RESULT_FILE), QUERY_NUM(QUERY_NUM), MIN_QUERY_SELECTIVELY(MIN_QUERY_SELECTIVELY), MAX_QUERY_SELECTIVELY(MAX_QUERY_SELECTIVELY)
			{
			}

			bool operator==(const EXP_PAR& other) const
			{
				return false;
			}
		};

		static void Exp_groupby::get_groups(const vector<vector<double>>& sample, const vector<vector<double>>& sub_sample, const GpType4Int &gp_rates4sample, const GpType4Int &gp_rates4sub_sample, const int GB_LEN, unordered_map<vector<int>, Group, VectorHash> &o_groups);
		static void get_group_sample_rates(SQLHANDLE &sqlconnectionhandle, double sample_rate,const vector<string> &GROUP_CONDITIONS, string db_name, string table_name, GpType4Str &o_group_rates);
		static void trans_group_rates(const vector<unordered_map<string, int>> &distinct_ids, GpType4Str &rates4str, GpType4Int &o_rates4int);
		static void write_exp_par(FILE *par_file, EXP_PAR exp_par);
		static void query_group(SQLHANDLE &sqlconnectionhandle, const vector<string> &GROUP_CONDITIONS, string db_name, string table_name, GpType4Str &o_group_size);
		static EXP_PAR get_exp_par();
		static double read_sample_str_format(SQLHANDLE &sqlconnectionhandle, vector<vector<string>> &o_table, string db_name, string table_name, string AGGREGATE_NAME, vector<string> CONDITION_NAMES);
		static void gen_sample_rates_vec(const vector<vector<double>>& sample, const GpType4Int &gp_rates4sample, int GB_LEN, vector<double> &o_sample_rate);
		static pair<double, double> read_str_samples(SQLHANDLE &sqlconnectionhandle, Settings& o_PAR, int run_num, vector<vector<string>>& o_sample, vector<vector<string>>& o_small_sample);
		static pair<double, double> gb_create_db_samples(SQLHANDLE &sqlconnectionhandle, int seed, string db_name, string table_name, pair<double, double> sample_rates, pair<string, string> sample_names, const vector<string> &GROUP_CONDITIONS, pair<GpType4Str, GpType4Str> &o_group_rates);
		static double gb_create_db_sample(SQLHANDLE &sqlconnectionhandle, int seed, string db_name, string table_name, double sample_rate, string sample_name, const vector<string> &GROUP_CONDITIONS, GpType4Str &o_group_rates);
	public:
		static int exp(SQLHANDLE& sqlconnectionhandle);

		Exp_groupby() = default;
		bool operator==(const Exp_groupby& other) const;
	};
}
