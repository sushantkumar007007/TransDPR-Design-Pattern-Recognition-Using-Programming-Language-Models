# Replication package
This repository contains a replication package for a paper "TransDPR: Design Pattern Recognition Using Programming Language Models". The paper has been submitted to ESEM 2023, Emerging ideas track. 

TransDPR is a design pattern recognition tool for C++ source files. The work is based on design pattern recognition of singleton and prototype design patterns

The tool is uses the language model developed by Facebook Research (TransCoder), which has two different pre-trained models (https://github.com/facebookresearch/TransCoder). We use model-1 in our work.

## Contents of the repository
The repository contains two parts:
1) The TransDPR tool for use on your own programs, or to replicate the study in the paper. 
2) Data from the paper, in the folder data. It can be used to replicate the study presented in the paper. The data is already annotated. 

## Dependencies and requirements
Following are the dependencies of the TransCoder:
* Python 3
* NumPy
* PyTorch
* fastBPE (generate and apply BPE codes)
* Moses (scripts to clean and tokenize text only - no installation required)
* Apex (for fp16 training)
* libclang (for C++ tokenization)
* submitit (to run the preprocessing pipeline on remote machine)
* six
* sacrebleu (pip install sacrebleu=="1.2.11")

The followings are the requirements for our work
* keras==2.12.0
* matplotlib==3.7.1
* numpy==1.22.4
* pandas==1.5.3
* scikit_learn==1.2.2
* scipy==1.10.1
* seaborn==0.12.2
* tensorflow==2.12.0
* tensorflow_hub==0.13.0
* tensorflow_text==2.12.1
* torch==2.0.1+cu118


## Configuration and execution
TransCoder needs to be configures in your local server, following the instruction provided at https://github.com/facebookresearch/TransCoder

Here is how to execute TransDPR:
1) Extract the embeddings of the programs using our "modifiied_translate.py" file. The tensor files of your program will be saved in the local directory as a .csv file. The command to extract embeddings: "*you_path/modifiied_translate.py --src_lang cpp --tgt_lang java --model_path *your_path/model_1.pth"

2) If you use this on your own data, and would like to evaluate the performance, please remember to annotate the data with the name of the pattern. Please take a look at the file df_csv_ed.csv for the example. 

3) Use TransDPR-1.py  with the logistic regression and RF models to evaluate the performance. You can run the TransDPR-1.py file on the .csv file to get the predictions.

4) Use Distanceplot2.py to visualize the distances. You can use all three dataset df_csv_ed.csv, df_onlyed.csv, and df_onlycsp.csv

5) Run the Classifier.py and import the data, e.g., df_csv_ed.csv. You will get results along with visulaitions. Run this file as a jupyter notebook file (ipynb), cell by cell.

6 ) The vc_test2.py is the file to replicate our results in industrial modules. You can run this file as a jupyter notebook file (ipynb), cell by cell. We collected the tensors and visualized the programs using PCA and t-SNE. We also calculated cosine distance to see how the programs are really close to each other in n-dimensional space.

## NDA
Unfortunately, we cannot share the tensor files for our CSP and ED modules because of a non-discloser agreement.
