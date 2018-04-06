"""Unit tests for detecting individual clusters."""

import pytest

import sys, os
sys.path.append(os.path.abspath('../lib'))
from tcc import structures, xyz, wrapper
from glob import glob
structures_to_test = glob('clusters/*.xyz')

def run_static_tcc_simple_bonds(x, box=[100.,100.,100.]):
    """Run TCC with pairwise cutoff bond detection algorithm.

    Args:
        x: cluster coordinates
        box: box side lengths for boundary conditions
    Returns:
        pandas table giving the static cluster information
    """
    TCC = wrapper.TCCWrapper()
    TCC.input_parameters['Simulation']['bond_type'] = wrapper.BondType.simple
    return TCC.run(box,x)

def run_static_tcc_voronoi(x, box=[100.,100.,100.]):
    """Run TCC with voronoi bond detection algorithm.

    Args:
        x: cluster coordinates
        box: box side lengths for boundary conditions
    Returns:
        pandas table giving the static cluster information
    """
    TCC = wrapper.TCCWrapper()
    return TCC.run(box,x)

@pytest.mark.parametrize('path', structures_to_test)
def test_simple_bonds(path):
    """Unit tests for clusters when running TCC with simple pairwise cutoff bond detection algorithm.

    Failure if number of detected clusters does not match known composition of given structure.

    Args:
        path: path to isolated structure geometry to run TCC on
    """
    x = xyz.read(path)
    cluster = path.split('/')[-1].split('.xyz')[0]

    found = run_static_tcc_simple_bonds(x)['Number of clusters']
    for component,n in structures.composition[cluster].items():
        assert n == int(found[component])

@pytest.mark.parametrize('path', structures_to_test)
def test_voronoi(path):
    """Unit tests for clusters when running TCC with simple pairwise cutoff bond detection algorithm.

    Failure if number of detected clusters does not match known composition of given structure.

    Args:
        path: path to isolated structure geometry to run TCC on
    """
    x = xyz.read(path)
    cluster = path.split('/')[-1].split('.xyz')[0]

    found = run_static_tcc_voronoi(x)['Number of clusters']
    for component,n in structures.composition[cluster].items():
        assert n == int(found[component])
