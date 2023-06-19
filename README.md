1) TransDPR is a design pattern recognition for C++ source files.
The work is based on design pattern recognition of singleton and prototype design patterns

2) TransCoder has two different pre-trained models (https://github.com/facebookresearch/TransCoder), we used model-1 in our work.

We used the model-1 pre-trainied model from FACEBOOK (TransCoder).

3) Following are the dependencies of the TransCoder
Python 3
NumPy
PyTorch
fastBPE (generate and apply BPE codes)
Moses (scripts to clean and tokenize text only - no installation required)
Apex (for fp16 training)
libclang (for C++ tokenization)
submitit (to run the preprocessing pipeline on remote machine)
six
sacrebleu (pip install sacrebleu=="1.2.11")


4) You have to configure the TransCoder in your local server, following the instruction provided at https://github.com/facebookresearch/TransCoder

5) The followings are the requirements for our work
keras==2.12.0
matplotlib==3.7.1
numpy==1.22.4
pandas==1.5.3
scikit_learn==1.2.2
scipy==1.10.1
seaborn==0.12.2
tensorflow==2.12.0
tensorflow_hub==0.13.0
tensorflow_text==2.12.1
torch==2.0.1+cu118


6) You can extract the embeddings of the programs using our "modifiied_translate.py" file

7) Run "modifiied_translate.py" to get the embeddings of your program. Please make sure you can run TransCoder in your system

8) After running this, the tensor files of your program will be saved in the local directory.

9) The command to extract embeddings
"run *you_path/modifiied_translate.py --src_lang cpp --tgt_lang java --model_path *your_path/model_1.pth"

10) Now save the embeddings of the programs and make a CSV file with implemented DPs labels.

11) Now TransDPR-1.py contains the logistic regression and RF models to evaluate the performance. You can run the TransDPR-1.py file on your data to get the predictions.

12 ) Please modify the path of dataset accordingly in Distanceplot2.py. You can use all three dataset df_csv_ed.csv, df_onlyed.csv, and df_onlycsp.csv
Run this file as a jupyter notebook file (ipynb), cell by cell.

13) You can run the Classifier.py by importing data (df_csv_ed.csv). You will get results along with visulaitions. Run this file as a jupyter notebook file (ipynb), cell by cell.

14) The vc_test2.py is the file to test our results in Volvo cars modules. You can run this file as a jupyter notebook file (ipynb), cell by cell.
15) We collected the tensors and visualized the programs using PCA and t-SNE.
16) We also calculated cosine distance to see how the programs are really close to each other in n-dimensional space.

Note: We cannot share the tensor files for our CSP and ED modules because of a non-discloser agreement.


