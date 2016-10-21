#!/usr/bin/python
import Renascence
def main():
    Renascence.setStreamPath("./")
    Renascence.setLibPath("./")
    producer = Renascence.init(["func.xml"])
    p_producer = Renascence.PieceFunctionProducer(producer, ['parallel.xml'], ['Map-Reduce.xml'])
    print p_producer.listType()
    sub_p_producer = Renascence.PieceFunctionProducerParallel(p_producer, 'server')
    print "sub_p_producer created"
    pfunction = sub_p_producer.createFunction('C(S(x0))', 'TrBmp')
    inputPieces = sub_p_producer.createInput('deps/Renascence/res/pictures/', 'TrBmp', [5])
    tempPiece = pfunction.run([inputPieces])
    outputPieces = sub_p_producer.createOutput('output/pythonTestParallel')
    sub_p_producer.copyPiece(tempPiece, outputPieces)

if __name__ == '__main__':
    main()
