/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "lmbd_convert.h"
using namespace std;
using namespace caffe;

/* LMBD environment variables */
MDB_env *mdb_env0;
MDB_dbi mdb_dbi0;
MDB_val mdb_key0, mdb_data0;
MDB_txn *mdb_txn0;

/* Two sets for the input and truth data sets */
MDB_env *mdb_env1;
MDB_dbi mdb_dbi1;
MDB_val mdb_key1, mdb_data1;
MDB_txn *mdb_txn1;

void open_input_db(char db_path[]) {
    /* OPEN LMDB FILE */
    std::cout << "Opening lmdb " << db_path << endl;
    mkdir(db_path, 0744);
    //    CHECK_EQ(mkdir(db_path, 0744), 0) << "mkdir " << db_path << "failed";
    CHECK_EQ(mdb_env_create(&mdb_env0), MDB_SUCCESS) << "mdb_env_create failed";
    CHECK_EQ(mdb_env_set_mapsize(mdb_env0, 1099511627776), MDB_SUCCESS) << "mdb_env_set_mapsize failed"; //1TB
    CHECK_EQ(mdb_env_open(mdb_env0, db_path, 0, 0664), MDB_SUCCESS) << "mdb_env_open failed";
    CHECK_EQ(mdb_txn_begin(mdb_env0, NULL, 0, &mdb_txn0), MDB_SUCCESS) << "mdb_txn_begin failed";
    CHECK_EQ(mdb_open(mdb_txn0, NULL, 0, &mdb_dbi0), MDB_SUCCESS) << "mdb_open failed. Does the lmdb already exist? ";
}

void open_truth_db(char db_path[]) {
    /* OPEN LMDB FILE */
    std::cout << "Opening lmdb " << db_path << endl;
    mkdir(db_path, 0744);
    //    CHECK_EQ(mkdir(db_path, 0744), 0) << "mkdir " << db_path << "failed";
    CHECK_EQ(mdb_env_create(&mdb_env1), MDB_SUCCESS) << "mdb_env_create failed";
    CHECK_EQ(mdb_env_set_mapsize(mdb_env1, 1099511627776), MDB_SUCCESS) << "mdb_env_set_mapsize failed"; //1TB
    CHECK_EQ(mdb_env_open(mdb_env1, db_path, 0, 0664), MDB_SUCCESS) << "mdb_env_open failed";
    CHECK_EQ(mdb_txn_begin(mdb_env1, NULL, 0, &mdb_txn1), MDB_SUCCESS) << "mdb_txn_begin failed";
    CHECK_EQ(mdb_open(mdb_txn1, NULL, 0, &mdb_dbi1), MDB_SUCCESS) << "mdb_open failed. Does the lmdb already exist? ";
}

void add_to_input_db(int item_id, float image[][SPECTRAL_DIM][SPATIAL_DIM]) {
    /* Define parameters of input data */
    Datum datum;
    datum.set_channels(3);
    datum.set_height(SPECTRAL_DIM);
    datum.set_width(SPATIAL_DIM);
    datum.set_data(image, CHANNELS * SPECTRAL_DIM * SPATIAL_DIM);

    /* Calculate input strings*/
    string value;
    string key_str = caffe::format_int(item_id, 8);
    datum.SerializeToString(&value);

    /* Write to database */
    mdb_data0.mv_size = value.size();
    mdb_data0.mv_data = reinterpret_cast<void*> (&value[0]);
    mdb_key0.mv_size = key_str.size();
    mdb_key0.mv_data = reinterpret_cast<void*> (&key_str[0]);
    CHECK_EQ(mdb_put(mdb_txn0, mdb_dbi0, &mdb_key0, &mdb_data0, 0), MDB_SUCCESS) << "mdb_put failed";

    /* Commit the database every once in while */
    if (++item_id % 1000 == 0) {
        CHECK_EQ(mdb_txn_commit(mdb_txn0), MDB_SUCCESS) << "mdb_txn_commit failed";
        CHECK_EQ(mdb_txn_begin(mdb_env0, NULL, 0, &mdb_txn0), MDB_SUCCESS) << "mdb_txn_begin failed";
    }
}

void add_to_truth_db(int item_id, float image[][SPECTRAL_DIM][SPATIAL_DIM]) {

    /* Define parameters of input data */
    Datum datum;
    datum.set_channels(3);
    datum.set_height(SPECTRAL_DIM);
    datum.set_width(SPATIAL_DIM);
    datum.set_data(image, CHANNELS * SPECTRAL_DIM * SPATIAL_DIM);
//    datum.set_float_data()
    
    
    /* Calculate input strings*/
    string value;
    string key_str = caffe::format_int(item_id, 8);
    datum.SerializeToString(&value);

    /* Write to database */
    mdb_data1.mv_size = value.size();
    mdb_data1.mv_data = reinterpret_cast<void*> (&value[0]);
    mdb_key1.mv_size = key_str.size();
    mdb_key1.mv_data = reinterpret_cast<void*> (&key_str[0]);
    CHECK_EQ(mdb_put(mdb_txn1, mdb_dbi1, &mdb_key1, &mdb_data1, 0), MDB_SUCCESS) << "mdb_put failed";

    /* Commit the database every once in while */
    if (++item_id % 1000 == 0) {
        CHECK_EQ(mdb_txn_commit(mdb_txn1), MDB_SUCCESS) << "mdb_txn_commit failed";
        CHECK_EQ(mdb_txn_begin(mdb_env1, NULL, 0, &mdb_txn1), MDB_SUCCESS) << "mdb_txn_begin failed";
    }
}

void close_input_db() {
    CHECK_EQ(mdb_txn_commit(mdb_txn0), MDB_SUCCESS) << "mdb_txn_commit failed";
    mdb_close(mdb_env0, mdb_dbi0);
    mdb_env_close(mdb_env0);
}

void close_truth_db() {
    CHECK_EQ(mdb_txn_commit(mdb_txn1), MDB_SUCCESS) << "mdb_txn_commit failed";
    mdb_close(mdb_env1, mdb_dbi1);
    mdb_env_close(mdb_env1);
}

void convert_dataset(char db_path[], int image[][SPECTRAL_DIM][CHANNELS]) {





    /* Define parameters of input data */
    Datum datum;
    datum.set_channels(3);
    datum.set_height(SPECTRAL_DIM);
    datum.set_width(SPATIAL_DIM);
    datum.set_data(image, CHANNELS * SPECTRAL_DIM * SPATIAL_DIM);


    /* Store in DB */
    string value;

    int item_id = 0; //FOR loop here

    /* Calculate input strings*/
    string key_str = caffe::format_int(item_id, 8);
    datum.SerializeToString(&value);

    /* Write to database */
    //    mdb_data.mv_size = value.size();
    //    mdb_data.mv_data = reinterpret_cast<void*> (&value[0]);
    //    mdb_key.mv_size = key_str.size();
    //    mdb_key.mv_data = reinterpret_cast<void*> (&key_str[0]);
    //    CHECK_EQ(mdb_put(mdb_txn, mdb_dbi, &mdb_key, &mdb_data, 0), MDB_SUCCESS) << "mdb_put failed";

    /* Commit the database every once in while */
    //    if (++count % 1000 == 0) {    
    //        CHECK_EQ(mdb_txn_commit(mdb_txn), MDB_SUCCESS) << "mdb_txn_commit failed";
    //        CHECK_EQ(mdb_txn_begin(mdb_env, NULL, 0, &mdb_txn), MDB_SUCCESS) << "mdb_txn_begin failed";   
    //    }

    /* Close database */
//    CHECK_EQ(mdb_txn_commit(mdb_txn), MDB_SUCCESS) << "mdb_txn_commit failed";
//    mdb_close(mdb_env, mdb_dbi);
//    mdb_env_close(mdb_env);
}